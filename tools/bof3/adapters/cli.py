"""Run a tool's ``main`` and turn a :class:`~bof3.errors.Bof3Error` into a message and exit code 1."""

from __future__ import annotations

import sys
from collections.abc import Callable

from bof3.errors import Bof3Error


def run_main(main: Callable[[], int | None]) -> int:
    """Return the exit code of ``main``; a core error prints its message to stderr and is 1."""
    try:
        return main() or 0
    except Bof3Error as error:
        print(error, file=sys.stderr)
        return 1
