"""The state a reviewed unit's source claims."""

from __future__ import annotations

from bof3.status import claims
from bof3.status import map as target_map


def unit_state(unit: target_map.Unit) -> str:
    """Exact / non_matching (by marker claim), untagged, or unlifted (no source)."""
    if unit.source is None:
        return "unlifted"
    marker = claims.read(unit.source, unit.vaddr, unit.names)
    if marker.claim_type == "matching":
        return "exact"
    return marker.claim_type or "untagged"
