# Multi-Armed Bandits Simulation

> ## ⚠️ Work in progress
> **This repository is incomplete and under active development.** Only the epsilon-greedy
> algorithm is implemented so far. Features listed in the roadmap are missing, the code has
> known rough edges, and the API/configuration may change without notice.

A small C++ simulator for the multi-armed bandit problem. Arms, rewards, run length, and output
locations are configured with JSON, so experiments can be changed without recompiling. Each run
writes reward and value-estimate histories to CSV and shows line plots.

## Implemented

- Epsilon-greedy agent with an exponential recency-weighted value update.
- Static arms (fixed reward, optional Gaussian drift) and Gaussian arms (`N(mean, std)`).
- Configurable `epsilon`, `alpha`, `steps`, output directory, and history file names.
- Per-step reward/arm history and per-arm estimate history written to CSV.
- Plots of the reward history and arm estimates via Matplot++.
- JSON parsing via RapidJSON, which is vendored in `lib/rapidjson`.

## Roadmap / not implemented yet

- [ ] **Export plots to image files** (PNG/SVG/PDF) instead of only displaying them.
- [ ] **More algorithms** — the arm selection policy is currently hard-coded to epsilon-greedy.
  Planned: Greedy, UCB1, and Gradient/Softmax bandit.
- [ ] Reproducible runs via a configurable random seed.
- [ ] Metrics such as cumulative reward, average reward, and regret.
- [ ] Multi-run averages with confidence bands.
- [ ] Tests, CI, and a sample config file.
- [ ] Code cleanup (RAII instead of raw owning pointers, naming fixes, CMake tidy-up).

See the source headers for the current, evolving design.

## Requirements

- CMake 3.10+ and a C++17 compiler
- Git and internet access for the first configure (Matplot++ is downloaded)
- [Gnuplot](https://sourceforge.net/projects/gnuplot/) on `PATH` for plot windows

## Build

```bash
cmake -S . -B build
cmake --build build --config Release
```

The executable is written to `build/bin/` (`MultiArmSim.exe` on Windows). Matplot++ is fetched
automatically on the first configure.

## Run

```bash
MultiArmSim <config_file_path>
```

```powershell
.\build\bin\MultiArmSim.exe .\config.json
```

Relative output paths are resolved from the current working directory, and missing output
directories are created automatically.

## Configuration

```json
{
  "epsilon": 0.1,
  "alpha": 0.1,
  "steps": 10000,
  "output": {
    "directory": "results",
    "rewardHistoryFile": "rewardHistory.csv",
    "armsEstimateHistoryFile": "armsEstimatedHistory.csv"
  },
  "arms": [
    { "type": "static", "value": 5.0 },
    { "type": "static", "value": 10.0, "drift": { "mean": 0.0, "std": 0.1 } },
    { "type": "gaussian", "mean": 7.0, "std": 1.0 }
  ]
}
```

| Key | Meaning |
| --- | --- |
| `epsilon` | Exploration probability (required, decimal, e.g. `0.1`). |
| `alpha` | Value-update step size (required, `0 < alpha <= 1`). |
| `steps` | Number of simulation iterations (required). |
| `output` | Optional output settings; all keys have defaults. |
| `arms[].type` | `"static"` or `"gaussian"` (required). |
| `arms[].value` | Base reward for a static arm. |
| `arms[].drift` | Optional `{ "mean", "std" }` Gaussian noise for a static arm. |
| `arms[].mean`, `arms[].std` | Normal reward distribution for a Gaussian arm. |

## Outputs

By default, files are written to `results/` (git-ignored):

| File | Content |
| --- | --- |
| `rewardHistory.csv` | `Step,SelectedArm,Reward` per step. |
| `armsEstimatedHistory.csv` | `Step,Q_0,...,Q_n` — estimated value per arm. |

Both histories are also plotted in a window.

## Project layout

```
├── CMakeLists.txt
├── include/          # Agent, Arm, Enviroment, config, reward, history, plotting
├── src/              # implementations
├── lib/rapidjson/    # vendored JSON library
├── results/          # generated output (git-ignored)
└── build/            # CMake build tree (git-ignored)
```

## License

Use it however you like , just don't forget to credit me, or my ghost will haunt your codebase.
