# ecs_benchmark
ECS benchmark comparison

 * [Creating entities](#creating-entities)
 * [Adding & removing components](#adding-removing-components)
 * [Iterating over entities with systems](#iterating-over-entities-with-systems)
 * [Ten randomized components](#ten-randomized-components)

## Frameworks
 * [EnTT](https://github.com/skypjack/entt) (SHA: [a95aa81850a3f42ee60ce78c66b2feb1de51dc1e](https://github.com/skypjack/entt/commit/a95aa81850a3f42ee60ce78c66b2feb1de51dc1e))
 * [flecs](https://github.com/SanderMertens/flecs) (SHA: [612c28635497c1749f8f3e84fa24eabfea58e05a](https://github.com/SanderMertens/flecs/commit/612c28635497c1749f8f3e84fa24eabfea58e05))

## Testing hardware
The measurements were obtained on a Macbook Pro 2018 model with a 2.6Ghz Intel i7, and 16GB of memory.

## Testing method
Each benchmark is isolated in its own function. Any datastructures required for the test are created during test setup, and teared down after the test has finished. Each benchmark is executed multiple times, and only the lowest measurement is reported. This is done to minimize the impact of scheduling, and to make sure measurements are taken when the data is hot (in the CPU cache).

## Benchmarks

### Creating entities

---
Entity creation, empty (n = 1000000):

| Framework | Measurement                        |
|-----------|------------------------------------|
|      EnTT |  0.003224                          |
|      EnTT |  0.003685 (batching)               |
|     Flecs |  0.002151                          |
|     Flecs |  0.000003 (batching)               |


---
Entity creation, 1 component (n = 1000000):

| Framework | Measurement                        |
|-----------|------------------------------------|
|      EnTT |  0.039316                          |
|      EnTT |  0.015816 (prealloc)               |
|      EnTT |  0.032884 (batching)               |
|      EnTT |  0.016294 (batching, prealloc)     |
|     Flecs |  0.117202                          |
|     Flecs |  0.101776 (prealloc)               |
|     Flecs |  0.040408 (batching)               |
|     Flecs |  0.041717 (batching, prealloc)     |


---
Entity creation, 2 component (n = 1000000):

| Framework | Measurement                        |
|-----------|------------------------------------|
|      EnTT |  0.078813                          |
|      EnTT |  0.110088 (group)                  |
|      EnTT |  0.048817 (prealloc)               |
|      EnTT |  0.076336 (batching)               |
|      EnTT |  0.031574 (batching, prealloc)     |
|      EnTT |  0.064007 (group, batch, prealloc) |
|     Flecs |  0.122279                          |
|     Flecs |  0.101844 (prealloc)               |
|     Flecs |  0.040467 (batching)               |
|     Flecs |  0.041660 (batching, prealloc)     |


---
Entity creation, 3 component (n = 1000000):

| Framework | Measurement                        |
|-----------|------------------------------------|
|      EnTT |  0.113421                          |
|      EnTT |  0.167172 (group)                  |
|      EnTT |  0.108624 (batching)               |
|      EnTT |  0.069154 (prealloc)               |
|      EnTT |  0.063494 (batching, prealloc)     |
|      EnTT |  0.118937 (group, batch, prealloc) |
|     Flecs |  0.125205                          |
|     Flecs |  0.103905 (prealloc)               |
|     Flecs |  0.039907 (batching)               |
|     Flecs |  0.040553 (batching, prealloc)     |


---
Entity deletion, 1 component (n = 1000000):

| Framework | Measurement                        |
|-----------|------------------------------------|
|      EnTT |  0.009806                          |
|     Flecs |  0.082979                          |


### Adding & removing components


---
Add one component (n = 1000000):

| Framework | Measurement                        |
|-----------|------------------------------------|
|      EnTT |  0.010895                          |
|     Flecs |  0.111899                          |
|     Flecs |  0.104188 (new w/component)        |
|     Flecs |  0.146509 (to existing)            |
|     Flecs |  0.012238 (to existing, bulk)      |


---
Add two components (n = 1000000):

| Framework | Measurement                        |
|-----------|------------------------------------|
|      EnTT |  0.044900                          |
|      EnTT |  0.070903 (group)                  |
|     Flecs |  0.256101                          |
|     Flecs |  0.111473 (w/type)                 |
|     Flecs |  0.012362 (to existing, bulk)      |


---
Add three components (n = 1000000):

| Framework | Measurement                        |
|-----------|------------------------------------|
|      EnTT |  0.064806                          |
|      EnTT |  0.111004 (group)                  |
|     Flecs |  0.421060                          |
|     Flecs |  0.118418 (w/type)                 |
|     Flecs |  0.029515 (to existing, bulk)      |


---
Add four components (n = 1000000):

| Framework | Measurement                        |
|-----------|------------------------------------|
|      EnTT |  0.084752                          |
|      EnTT |  0.152488 (group)                  |
|     Flecs |  0.621154                          |
|     Flecs |  0.138415 (w/type)                 |


---
Remove one component (n = 1000000):

| Framework | Measurement                        |
|-----------|------------------------------------|
|      EnTT |  0.006068                          |
|      EnTT |  0.005965 (2 components)           |
|      EnTT |  0.028722 (2 components, group)    |
|     Flecs |  0.080064                          |
|     Flecs |  0.120113 (2 components)           |
|     Flecs |  0.012244 (2 components, bulk)     |


---
Remove two components (n = 1000000):

| Framework | Measurement                        |
|-----------|------------------------------------|
|      EnTT |  0.013665                          |
|      EnTT |  0.036981 (group)                  |
|     Flecs |  0.190336                          |
|     Flecs |  0.083298 (w/type)                 |


---
Remove three components (n = 1000000):

| Framework | Measurement                        |
|-----------|------------------------------------|
|      EnTT |  0.026296                          |
|      EnTT |  0.066102 (group)                  |
|     Flecs |  0.314449                          |
|     Flecs |  0.086049 (w/type)                 |


---
Remove four components (n = 1000000):

| Framework | Measurement                        |
|-----------|------------------------------------|
|      EnTT |  0.044339                          |
|      EnTT |  0.094290 (group)                  |
|     Flecs |  0.508216                          |
|     Flecs |  0.088344 (w/type)                 |


### Iterating over entities with systems


---
Iterate, one component (n = 1000000):

| Framework | Measurement                        |
|-----------|------------------------------------|
|      EnTT |  0.000410 (view)                   |
|     Flecs |  0.000364                          |


---
Iterate, two components (n = 1000000):

| Framework | Measurement                        |
|-----------|------------------------------------|
|      EnTT |  0.001623 (view)                   |
|      EnTT |  0.000620 (group, owning)          |
|     Flecs |  0.000596                          |


---
Iterate, two components, eight types (n = 1000000):

| Framework | Measurement                        |
|-----------|------------------------------------|
|      EnTT |  0.001641 (view)                   |
|      EnTT |  0.000630 (group, owning)          |
|     Flecs |  0.000628                          |


---
Iterate, two components, eight types, four matching (n = 1000000):

| Framework | Measurement                        |
|-----------|------------------------------------|
|      EnTT |  0.002883 (view)                   |
|      EnTT |  0.000632 (group, owning)          |
|     Flecs |  0.000625                          |


---
Iterate, three components (n = 1000000):

| Framework | Measurement                        |
|-----------|------------------------------------|
|      EnTT |  0.002457 (view)                   |
|      EnTT |  0.000852 (group, owning)          |
|     Flecs |  0.000766                          |


---
Iterate, three components, two types (n = 1000000):

| Framework | Measurement                        |
|-----------|------------------------------------|
|      EnTT |  0.002020 (view)                   |
|      EnTT |  0.000850 (group, owning)          |
|     Flecs |  0.000777                          |


---
Iterate, three components, eight types (n = 1000000):

| Framework | Measurement                        |
|-----------|------------------------------------|
|      EnTT |  0.002383 (view)                   |
|      EnTT |  0.000849 (group, owning)          |
|     Flecs |  0.000773                          |


---
Iterate, three components, eight types, four matching (n = 1000000):

| Framework | Measurement                        |
|-----------|------------------------------------|
|      EnTT |  0.004433 (view)                   |
|      EnTT |  0.000851 (group, owning)          |
|     Flecs |  0.000777                          |


---
Iterate, four components, eight types (n = 1000000):

| Framework | Measurement                        |
|-----------|------------------------------------|
|      EnTT |  0.002399 (view)                   |
|      EnTT |  0.001087 (group, owning)          |
|     Flecs |  0.001088                          |


---
Iterate, four components, eight types, four matching (n = 1000000):

| Framework | Measurement                        |
|-----------|------------------------------------|
|      EnTT |  0.004400 (view)                   |
|      EnTT |  0.001080 (group, owning)          |
|     Flecs |  0.001045                          |


### Ten randomized components


---
Pathological, one component, 1024 types (n = 1000000):

| Framework | Measurement                        |
|-----------|------------------------------------|
|      EnTT |  0.000411 (view)                   |
|     Flecs |  0.000511                          |


---
Pathological, two components, 1024 types (n = 1000000):

| Framework | Measurement                        |
|-----------|------------------------------------|
|      EnTT |  0.001609 (view)                   |
|      EnTT |  0.000619 (group, owning)          |
|     Flecs |  0.000789                          |


---
Pathological, three components, 1024 types (n = 1000000):

| Framework | Measurement                        |
|-----------|------------------------------------|
|      EnTT |  0.002364 (view)                   |
|      EnTT |  0.000847 (group, owning)          |
|     Flecs |  0.001079                          |


---
Pathological, four components, 1024 types (n = 1000000):

| Framework | Measurement                        |
|-----------|------------------------------------|
|      EnTT |  0.003517 (view)                   |
|      EnTT |  0.001069 (group, owning)          |
|     Flecs |  0.001343                          |
