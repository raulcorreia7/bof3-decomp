from worklist import attempts


def test_attempts_keep_each_record(tmp_path):
    path = tmp_path / "attempts.tsv"
    path.write_text(
        "function\ttried\tfirst_diff\tscore\n"
        "image@0x80000000\tloop\tload\t90%\n"
        "image@0x80000000\tpointer\t\t\n"
        "other@0x80000000\tbranch\t\t\n"
    )
    assert attempts(path) == {
        "image@0x80000000": "loop; load; 90% | pointer",
        "other@0x80000000": "branch",
    }
