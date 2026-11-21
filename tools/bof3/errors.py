"""The failures the core reports; a tool's ``main`` turns one into a message and an exit code."""

from __future__ import annotations


class Bof3Error(Exception):
    """A defect the user fixes; the message states the fix."""


class MissingInputError(Bof3Error):
    """A file or build output the work needs is not there."""


class UnknownFunctionError(Bof3Error):
    """A ``TARGET@NAME`` spec is malformed or names no function of the index."""


class SymbolError(Bof3Error):
    """A symbol verb's input names no row, file, record or target, or a check fails."""


class RenameError(SymbolError):
    """A rename is refused before it changes a file, or fails and is rolled back."""
