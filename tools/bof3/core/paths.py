"""The repository root and its top-level directory names; a short-lived tool loads it fast."""

from pathlib import Path

ROOT = Path(__file__).resolve().parents[3]

BUILD = "build"
ASM = "asm"  # authored assembly
SPLIT_ASM = "build/asm"  # splat output
CONFIG = "config"
TOOLCHAINS = "toolchains"
INPUTS = "inputs"
