#!/usr/bin/env bash
set -euo pipefail
echo "[SMOKE] Running 2 producers for 6s..."
./bin/smart_factory_sim --producers 2 --duration 6 --rate 8 --seed 1
echo "[SMOKE] Done. Files:"
ls -l events.log snapshot.txt || true
echo "[SMOKE] Head of events.log:"
head -n 5 events.log || true