import shutil
import subprocess
from pathlib import Path

SCRIPT = Path(__file__).resolve().parents[1] / "check_asm.sh"
LINE = 'INCLUDE_ASM("asm/{}", {});\n'


def git(repo: Path, *args: str) -> None:
    subprocess.run(
        ["git", "-c", "user.name=t", "-c", "user.email=t@t", *args],
        cwd=repo,
        check=True,
        capture_output=True,
    )


def write(repo: Path, image: str, count: int) -> None:
    path = repo / "src" / image / "f.c"
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_text("".join(LINE.format(image, i) for i in range(count)))


def make_repo(tmp_path: Path) -> Path:
    repo = tmp_path / "repo"
    (repo / "tools").mkdir(parents=True)
    shutil.copy(SCRIPT, repo / "tools" / "check_asm.sh")
    git(repo, "init", "-q", "-b", "main")
    write(repo, "engine/game/00", 2)
    write(repo, "overlays/menu/shop/00", 1)
    write(repo, "engine/slus", 1)
    git(repo, "add", "-A")
    git(repo, "commit", "-qm", "base")
    git(repo, "checkout", "-qb", "work")
    return repo


def run(repo: Path) -> subprocess.CompletedProcess:
    return subprocess.run(
        ["sh", "tools/check_asm.sh", "main"],
        cwd=repo,
        capture_output=True,
        text=True,
        check=False,
    )


def test_lost_match_offset_by_new_one_elsewhere_fails(tmp_path: Path) -> None:
    repo = make_repo(tmp_path)
    write(repo, "engine/game/00", 1)
    write(repo, "overlays/menu/shop/00", 2)
    result = run(repo)
    assert result.returncode == 1
    assert "image shop/00 has 2 INCLUDE_ASM, 1 at the merge base" in result.stderr
    assert "game/00" not in result.stderr
