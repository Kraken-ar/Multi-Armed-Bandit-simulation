# Multi-Armed Bandits Simulation

A small, object-oriented C++ simulator for the **multi-armed bandit** problem. It builds an
environment of configurable arms, lets an agent explore/exploit them for a number of steps,
tracks the rewards and the agent's value estimates, writes them to CSV, and plots them.

Everything (epsilon, learning rate, arm reward distributions, number of steps, output paths, ...) is driven
by a JSON configuration file, so experiments can be changed without recompiling.

> **Status:** early-stage research/learning project. The core simulation works; the roadmap at
> the bottom lists the planned features (image export, pluggable policies such as Greedy, UCB
> and Gradient bandit, ...).

---

## Features

- **Epsilon-greedy agent** with an exponential recency-weighted value update.
- **Configurable arms** via JSON:
  - `static` arms — fixed reward, optionally with Gaussian noise and a drifting (random-walk) reward.
  - `gaussian` arms — reward sampled from `N(mean, std)` on every pull.
- **Policy/agent hyper-parameters** from config: `epsilon` and `alpha`.
- **Configurable run length and outputs** — `steps`, the results directory, and both history
  file names come from the config; the directory is created automatically.
- **History tracking**:
  - reward + selected arm per step → `<output.directory>/<output.rewardHistoryFile>`
  - estimated value of every arm per step → `<output.directory>/<output.armsEstimateHistoryFile>`
- **Line plots** of the reward history and of all arms' value estimates (Matplot++).
- **Layered design** (reward models, agent, environment, tracking, plotting, config parsing)
  that is meant to be extended with new algorithms and reward types.
- **JSON parsing** with [RapidJSON](https://github.com/Tencent/rapidjson) (vendored in `lib/`).
- **Plotting** with [Matplot++](https://github.com/alandefreitas/matplotplusplus) (fetched by CMake).

---

## Project structure

```
Multi-Armed-Bandits-Simulation/
├── CMakeLists.txt              # build definition (fetches Matplot++ via FetchContent)
├── README.md
├── include/                    # public headers
│   ├── Agent.hpp               # eps-greedy agent + ArmData
│   ├── Arm.hpp                 # arm = reward-model wrapper
│   ├── Enviroment.hpp          # simulation loop, owns agent + arms + trackers
│   ├── SimulationBuilder.hpp   # builds Agent/Enviroment from a config file
│   ├── config/
│   │   └── ConfigReader.hpp    # JSON config parsing + validation
│   ├── reward/
│   │   ├── RewardModel.hpp     # abstract reward model
│   │   ├── StaticRewardModel.hpp
│   │   └── GaussianRewardModel.hpp
│   ├── history/
│   │   ├── RewardHistoryTracker.hpp
│   │   └── ArmsEstematedHistoryTracker.hpp
│   └── plotting/
│       ├── Plotter.hpp         # generic Plotter<T> interface
│       └── LinePlotter.hpp     # line-plot implementation
├── src/                        # implementation files (mirrors include/)
├── lib/rapidjson/              # vendored JSON library
├── results/                    # generated CSV history (git-ignored)
└── build/                      # CMake build tree (git-ignored)
```

### Architecture

```
             ┌────────────────────┐
             │      main.cpp      │
             └─────────┬──────────┘
                       │ config path
             ┌─────────▼──────────┐        ┌───────────────────┐
             │ SimulationBuilder  │───────▶│    ConfigReader   │  RapidJSON
             └─────────┬──────────┘        └───────────────────┘
                       │ creates
        ┌──────────────┴───────────────┐
        ▼                              ▼
┌───────────────┐             ┌────────────────┐
│     Agent     │◀────────────│   Enviroment   │
│ eps-greedy Q  │   action    │     fit()      │
└───────────────┘   /reward  └───────┬────────┘
                                    │ pulls
                          ┌─────────▼─────────┐
                          │       Arm         │
                          │  RewardModel*     │
                          └─────────┬─────────┘
                     ┌──────────────┴──────────────┐
                     ▼                             ▼
          ┌────────────────────┐        ┌────────────────────┐
          │ StaticRewardModel  │        │ GaussianRewardModel│
          └────────────────────┘        └────────────────────┘

Enviroment also owns:
  RewardHistoryTracker ──────▶ LinePlotter ─▶ window / CSV
  ArmsEstematedHistoryTracker ┘
```

### Simulation loop

`Enviroment::fit()` repeats `steps` times, where `steps` comes from the config:

1. `Agent::makeAction()` — with probability `epsilon` pick a random arm, otherwise pick the arm
   with the highest estimated value (ties go to the lowest arm id).
2. `Arm::getReward()` — ask the arm's reward model for a sample.
3. `Agent::updateArmData(armId, reward)` — update the estimate:
   `Q(arm) ← Q(arm) + alpha * (reward − Q(arm))` and increment the pull count.
4. Record the `(step, selected arm, reward)` and the current estimate of every arm.

After the loop the history is written to the configured output directory and both plots are shown.

---

## Requirements

- CMake **3.10+**
- A C++17-capable compiler (tested with MinGW/GCC on Windows; MSVC and Clang should work)
- Git and an internet connection for the first configure (Matplot++ is downloaded)
- [Gnuplot](https://sourceforge.net/projects/gnuplot/) available on `PATH` for the interactive
  plot windows used by Matplot++

---

## Build

```bash
# from the repository root
cmake -S . -B build
cmake --build build --config Release
```

The first configure downloads Matplot++ with `FetchContent`. The executable is written to
`build/bin/` (`MultiArmSim` / `MultiArmSim.exe`).

Using MinGW/Ninja instead of the default generator:

```powershell
cmake -S . -B build -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release
cmake --build build
```

---

## Usage

```bash
MultiArmSim <config_file_path>
```

Relative output paths are resolved from the current working directory, and the output directory
is created automatically if it does not exist.

```powershell
# Windows example
.\build\bin\MultiArmSim.exe .\config.json

# Linux / macOS
./build/bin/MultiArmSim ./config.json
```

### Example configuration

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
    { "type": "gaussian", "mean": 7.0, "std": 1.0 },
    { "type": "gaussian", "mean": 3.0, "std": 2.0 }
  ]
}
```

### Configuration reference

| Key | Type | Required | Meaning |
| --- | --- | --- | --- |
| `epsilon` | double | yes | Exploration probability, `0.0` = pure greedy, `1.0` = pure random. Write it as a decimal (`0.1`, not `0`); the validator uses RapidJSON's `IsDouble()`. |
| `alpha` | double | yes | Step size of the value update. `0 < alpha ≤ 1`; `1.0` means "use the last reward only". |
| `steps` | int | yes | Number of simulation iterations. |
| `output` | object | no | Output directory and file names. All keys are optional and fall back to the defaults below. |
| `output.directory` | string | no | Directory for generated history files (default `results`). Created if missing. |
| `output.rewardHistoryFile` | string | no | Reward history file name (default `rewardHistory.csv`). |
| `output.armsEstimateHistoryFile` | string | no | Arms estimate history file name (default `armsEstimatedHistory.csv`). |
| `arms` | array | yes | At least one arm. |
| `arms[].type` | string | yes | `"static"` or `"gaussian"`. Unknown values are treated as `"gaussian"`. |
| `arms[].value` | number | static only | Base reward of a static arm. |
| `arms[].drift.mean` | number | no | Mean of the Gaussian noise added to a static arm. |
| `arms[].drift.std` | number | no | Standard deviation of that noise. |
| `arms[].mean` | number | gaussian only | Mean of the arm's normal reward distribution. |
| `arms[].std` | number | gaussian only | Standard deviation of the arm's normal reward distribution. |

Notes on static arms:

- Config-created static arms are always **noisy** (`isNoisy = true`); without a `drift` object
  the noise is `N(0, 0)`, so they behave deterministically.
- When `drift` is present, the noise is added **and accumulated** into the arm's base value
  (`rewardValue += noise`), i.e. the arm's expected reward performs a random walk. With
  `drift: { "mean": 0, "std": 0.1 }` this is a drift/diffusion process, not just i.i.d. noise.
- A `gaussian` arm is re-sampled from `N(mean, std)` on every pull and does not drift.
- There is no reward clipping, so a Gaussian arm can return negative rewards.

---

## Outputs

With the default `output` configuration, files are written to `results/`:

| Path | Content |
| --- | --- |
| `results/rewardHistory.csv` | `Step,SelectedArm,Reward` — one row per step. |
| `results/armsEstimatedHistory.csv` | `Step,Q_0,...,Q_n` — value estimate of each arm per step. |
| Plot window 1 | Reward history line plot. |
| Plot window 2 | One line per arm: its estimated value over time. |

Open the CSVs with any spreadsheet tool, pandas, etc.:

```python
import pandas as pd

rewards = pd.read_csv("results/rewardHistory.csv")
estimates = pd.read_csv("results/armsEstimatedHistory.csv")
print(rewards["Reward"].mean())
print(rewards["SelectedArm"].value_counts())
```

---

## Design notes

- `RewardModel` is the abstract strategy for reward generation (`getSample()`), so new reward
  distributions can be added without touching the environment.
- `Arm` wraps a `RewardModel*`, keeping the environment agnostic of the distribution.
- `Agent` holds per-arm statistics (`ArmData`: id, last estimate, times played) and implements
  the current epsilon-greedy policy inline in `makeAction()`.
- `ConfigReader` validates JSON keys/types and is the only place that knows the config schema;
  `SimulationBuilder` is a thin facade used by `main`.
- `Plotter<T>` / `LinePlotter` separate data collection (`*HistoryTracker`) from rendering.

### Known limitations

- The action-selection policy is **hard-coded** to epsilon-greedy inside `Agent`.
- Only the last estimate per arm is exposed; UCB/gradient methods will need pull counts,
  reward baselines, and per-arm preference values.
- Plots are only displayed; there is no image-export option yet.
- Raw owning pointers are used throughout; `Enviroment::~Enviroment` mixes `free()` with
  `new`-allocated objects. Converting to `std::unique_ptr` / value semantics is advisable.
- `std::random_device` is used to seed a fresh generator on every sample, so runs are not
  reproducible/seeded.
- Typographical names (`Enviroment`, `Estemated`, `epslon`) are part of the current API.

---

## Roadmap / TODO

### 1. Export plots as image files

- [ ] Add image-export options to the `output` config section.
- [ ] Support `png`, `svg`, and `pdf` formats and use `output.directory` for the image paths.
- [ ] Use Matplot++'s `save()` instead of (or in addition to) `show()`, e.g.
      `matplot::save("results/reward_history.png")`, and optionally run headless (`show()` off)
      so the simulator can run on CI/servers without a display.
- [ ] Make drawing, saving, and CSV export independently toggleable.

### 2. Multiple action-selection policies (not just epsilon-greedy)

- [ ] Extract a `Policy` interface (e.g. `selectArm(const std::vector<ArmData>&)` and
      `update(armId, reward)`), and make `Agent` delegate to it.
- [ ] Add a `"policy"` key to the JSON config (default: `"epsilon_greedy"`) with
      policy-specific hyper-parameters.
- [ ] Implement:
  - [ ] **Greedy** — always exploit; optional optimistic initial values to force exploration.
  - [ ] **Epsilon-greedy** — current behaviour, kept as the default.
  - [ ] **UCB1** — `Q(a) + c * sqrt(ln(t) / N(a))`, with configurable `c`; needs pull counts
        (`timesPlayed` already exists) and a guarantee that every arm is tried once.
  - [ ] **Gradient / Softmax bandit** — preferences `H(a)`, `pi(a) = softmax(H)(a)`, updated with
        `H(a) += alpha * (R - R̄) * (1{a selected} - pi(a))`, with a configurable baseline.
  - [ ] (Stretch) Thompson sampling and optimistic initial values as variants.
- [ ] Track policy-specific diagnostics (e.g. softmax probabilities, UCB bounds) for plotting.
- [ ] Add unit tests comparing each policy on deterministic/statistical test cases.

### 3. Simulation correctness & reproducibility

- [ ] Add a `seed` option and keep one seeded PRNG per simulation for reproducible runs.
- [ ] Report cumulative reward, average reward and regret against the best arm.
- [ ] Support repeated runs and plot means with confidence bands.
- [ ] Resolve relative output paths against the config file location.

### 4. Code quality

- [ ] Replace raw owning pointers with RAII (`std::unique_ptr`, `std::vector<Arm>`), and fix the
      `free()`/`delete` mismatch.
- [ ] Rename `Enviroment` → `Environment`, `Estemated` → `Estimated`, `epslon` → `epsilon`
      (with a compatibility alias if needed).
- [ ] Add a `config.example.json` and validate it in CI.
- [ ] Add tests/CI (configure, build, run a short headless simulation, assert CSV columns).
- [ ] Tidy the CMakeLists (duplicate `target_include_directories`, pin the Matplot++ tag/version).

---

## License

No license file is present in the repository yet. Add one before distributing or reusing the
code.
