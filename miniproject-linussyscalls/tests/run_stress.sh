#!/usr/bin/env bash
set -euo pipefail
echo "[STRESS] Running 4 producers for 10s..."
./bin/smart_factory_sim --producers 4 --duration 10 --rate 20 --seed 7
echo "[STRESS] Done. Total lines in events.log:"
wc -l events.log || true