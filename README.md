# ecs_benchmark
ECS benchmark comparison

 * [Creating entities](#creating-entities)
 * [Adding & removing components](#adding-removing-components)
 * [Iterating over entities with systems](#iterating-over-entities-with-systems)
 * [Ten randomized components](#ten-randomized-components)

## Frameworks
 * [EnTT](https://github.com/skypjack/entt) (SHA: [fc8e8874a9b29523a5370a959035ee57b7d2be51](https://github.com/skypjack/entt/commit/a95aa81850a3f42ee60ce78c66b2feb1de51dc1e))
 * [flecs](https://github.com/SanderMertens/flecs) (SHA: [d384ab66593d4ee9da08e72afba75296130f0727](https://github.com/SanderMertens/flecs/commit/612c28635497c1749f8f3e84fa24eabfea58e05))

## Testing hardware
The measurements were obtained on a Macbook Pro 2019 model with a 2.3Ghz Intel i9, and 32GB of memory.

## Testing method
Each benchmark is isolated in its own function. Any datastructures required for the test are created during test setup, and teared down after the test has finished. Each benchmark is executed multiple times, and only the lowest measurement is reported. This is done to minimize the impact of scheduling, and to make sure measurements are taken when the data is hot (in the CPU cache).


## Benchmarks
The benchmarks are reported in seconds, where the number represents N iterations of the test. If a test takes 0.04 seconds and n = 1000000, each individual operation took (0.04 / 1000000) seconds. For every test, lower numbers are better.

### Creating entities

---
Entity creation, empty (n = 1000000):

| Framework | Measurement                        |
|-----------|------------------------------------|
|      EnTT |  0.003870                          |
|      EnTT |  0.003065 (batching)               |
|     Flecs |  0.018094                          |
|     Flecs |  0.006888 (batching)               |


---
Entity creation, 1 component (n = 1000000):

| Framework | Measurement                        |
|-----------|------------------------------------|
|      EnTT |  0.022670                          |
|      EnTT |  0.018897 (prealloc)               |
|      EnTT |  0.019480 (batching)               |
|      EnTT |  0.016514 (batching, prealloc)     |
|     Flecs |  0.044926                          |
|     Flecs |  0.037425 (prealloc)               |
|     Flecs |  0.014765 (batching)               |
|     Flecs |  0.015720 (batching, prealloc)     |


---
Entity creation, 2 component (n = 1000000):

| Framework | Measurement                        |
|-----------|------------------------------------|
|      EnTT |  0.042104                          |
|      EnTT |  0.080939 (group)                  |
|      EnTT |  0.034699 (prealloc)               |
|      EnTT |  0.038610 (batching)               |
|      EnTT |  0.032507 (batching, prealloc)     |
|      EnTT |  0.062649 (group, batch, prealloc) |
|     Flecs |  0.048187                          |
|     Flecs |  0.040486 (prealloc)               |
|     Flecs |  0.014902 (batching)               |
|     Flecs |  0.014654 (batching, prealloc)     |


---
Entity creation, 3 component (n = 1000000):

| Framework | Measurement                        |
|-----------|------------------------------------|
|      EnTT |  0.059416                          |
|      EnTT |  0.116126 (group)                  |
|      EnTT |  0.058059 (batching)               |
|      EnTT |  0.050729 (prealloc)               |
|      EnTT |  0.048765 (batching, prealloc)     |
|      EnTT |  0.100343 (group, batch, prealloc) |
|     Flecs |  0.052634                          |
|     Flecs |  0.045955 (prealloc)               |
|     Flecs |  0.015573 (batching)               |
|     Flecs |  0.016451 (batching, prealloc)     |


---
Entity deletion, 1 component (n = 1000000):

| Framework | Measurement                        |
|-----------|------------------------------------|
|      EnTT |  0.010127                          |
|     Flecs |  0.036865                          |
|     Flecs |  0.016990 (bulk)                   |


---
Entity deletion, 4 components (n = 1000000):

| Framework | Measurement                        |
|-----------|------------------------------------|
|      EnTT |  0.049088                          |
|      EnTT |  0.092837 (group)                  |
|     Flecs |  0.049732                          |
|     Flecs |  0.017624 (bulk)                   |


---
Entity deletion, 8 components (n = 1000000):

| Framework | Measurement                        |
|-----------|------------------------------------|
|      EnTT |  0.092880                          |
|      EnTT |  0.146413 (group, 4 full/4 partial own)      |
|     Flecs |  0.067478                          |
|     Flecs |  0.019204 (bulk)                   |


### Adding & removing components


---
Add one component (n = 1000000):

| Framework | Measurement                        |
|-----------|------------------------------------|
|      EnTT |  0.012636                          |
|     Flecs |  0.035525                          |
|     Flecs |  0.038956 (new w/component)        |
|     Flecs |  0.035941 (add_w_entity)           |
|     Flecs |  0.036433 (tag)                    |
|     Flecs |  0.037360 (switch)                 |
|     Flecs |  0.068055 (existing)               |
|     Flecs |  0.036701 (existing, switch)       |
|     Flecs |  0.073065 (existing w/4)           |
|     Flecs |  0.037329 (existing w/4, switch)   |
|     Flecs |  0.001336 (existing, bulk)         |


---
Add two components (n = 1000000):

| Framework | Measurement                        |
|-----------|------------------------------------|
|      EnTT |  0.023120                          |
|      EnTT |  0.043995 (group)                  |
|     Flecs |  0.100147                          |
|     Flecs |  0.038404 (w/type)                 |
|     Flecs |  0.001359 (to existing, bulk)      |


---
Add three components (n = 1000000):

| Framework | Measurement                        |
|-----------|------------------------------------|
|      EnTT |  0.028946                          |
|      EnTT |  0.074408 (group)                  |
|     Flecs |  0.179340                          |
|     Flecs |  0.041655 (w/type)                 |
|     Flecs |  0.001334 (to existing, bulk)      |


---
Add four components (n = 1000000):

| Framework | Measurement                        |
|-----------|------------------------------------|
|      EnTT |  0.044150                          |
|      EnTT |  0.107176 (group)                  |
|     Flecs |  0.264137                          |
|     Flecs |  0.053842 (w/type)                 |


---
Remove one component (n = 1000000):

| Framework | Measurement                        |
|-----------|------------------------------------|
|      EnTT |  0.005377                          |
|      EnTT |  0.005452 (2 components)           |
|      EnTT |  0.027950 (2 components, group)    |
|     Flecs |  0.036387                          |
|     Flecs |  0.072693 (2 components)           |
|     Flecs |  0.001337 (2 components, bulk)     |


---
Remove two components (n = 1000000):

| Framework | Measurement                        |
|-----------|------------------------------------|
|      EnTT |  0.014079                          |
|      EnTT |  0.037887 (group)                  |
|     Flecs |  0.103395                          |
|     Flecs |  0.040435 (w/type)                 |


---
Remove three components (n = 1000000):

| Framework | Measurement                        |
|-----------|------------------------------------|
|      EnTT |  0.025739                          |
|      EnTT |  0.065702 (group)                  |
|     Flecs |  0.181903                          |
|     Flecs |  0.045522 (w/type)                 |


---
Remove four components (n = 1000000):

| Framework | Measurement                        |
|-----------|------------------------------------|
|      EnTT |  0.040281                          |
|      EnTT |  0.083085 (group)                  |
|     Flecs |  0.268287                          |
|     Flecs |  0.049743 (w/type)                 |


### Iterating over entities with systems


---
Iterate, one component (n = 1000000):

| Framework | Measurement                        |
|-----------|------------------------------------|
|      EnTT |  0.000299 (view)                   |
|     Flecs |  0.000293                          |


---
Iterate, two components (n = 1000000):

| Framework | Measurement                        |
|-----------|------------------------------------|
|      EnTT |  0.001315 (view)                   |
|      EnTT |  0.000450 (group, owning)          |
|     Flecs |  0.000451                          |


---
Iterate, two components, eight types (n = 1000000):

| Framework | Measurement                        |
|-----------|------------------------------------|
|      EnTT |  0.001321 (view)                   |
|      EnTT |  0.000454 (group, owning)          |
|     Flecs |  0.000441                          |


---
Iterate, two components, eight types, four matching (n = 1000000):

| Framework | Measurement                        |
|-----------|------------------------------------|
|      EnTT |  0.002476 (view)                   |
|      EnTT |  0.000456 (group, owning)          |
|     Flecs |  0.000450                          |


---
Iterate, three components (n = 1000000):

| Framework | Measurement                        |
|-----------|------------------------------------|
|      EnTT |  0.001975 (view)                   |
|      EnTT |  0.000681 (group, owning)          |
|     Flecs |  0.000646                          |


---
Iterate, three components, eight types (n = 1000000):

| Framework | Measurement                        |
|-----------|------------------------------------|
|      EnTT |  0.002018 (view)                   |
|      EnTT |  0.000683 (group, owning)          |
|     Flecs |  0.000646                          |


---
Iterate, three components, eight types, four matching (n = 1000000):

| Framework | Measurement                        |
|-----------|------------------------------------|
|      EnTT |  0.003940 (view)                   |
|      EnTT |  0.000687 (group, owning)          |
|     Flecs |  0.000657                          |


---
Iterate, four components, eight types (n = 1000000):

| Framework | Measurement                        |
|-----------|------------------------------------|
|      EnTT |  0.002013 (view)                   |
|      EnTT |  0.000855 (group, owning)          |
|     Flecs |  0.000887                          |


### Ten randomized components


---
Pathological, one component, 1024 types (n = 1000000):

| Framework | Measurement                        |
|-----------|------------------------------------|
|      EnTT |  0.000304 (view)                   |
|     Flecs |  0.000359                          |


---
Pathological, two components, 1024 types (n = 1000000):

| Framework | Measurement                        |
|-----------|------------------------------------|
|      EnTT |  0.001316 (view)                   |
|      EnTT |  0.000448 (group, owning)          |
|     Flecs |  0.000607                          |


---
Pathological, three components, 1024 types (n = 1000000):

| Framework | Measurement                        |
|-----------|------------------------------------|
|      EnTT |  0.002022 (view)                   |
|      EnTT |  0.000672 (group, owning)          |
|     Flecs |  0.000908                          |


---
Pathological, four components, 1024 types (n = 1000000):

| Framework | Measurement                        |
|-----------|------------------------------------|
|      EnTT |  0.003207 (view)                   |
|      EnTT |  0.000884 (group, owning)          |
|     Flecs |  0.001198                          |
