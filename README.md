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
|      EnTT |  0.003787                          |
|      EnTT |  0.002783 (batching)               |
|     Flecs |  0.017694                          |
|     Flecs |  0.005882 (batching)               |


---
Entity creation, 1 component (n = 1000000):

| Framework | Measurement                        |
|-----------|------------------------------------|
|      EnTT |  0.018396                          |
|      EnTT |  0.015558 (prealloc)               |
|      EnTT |  0.015655 (batching)               |
|      EnTT |  0.014335 (batching, prealloc)     |
|     Flecs |  0.043771                          |
|     Flecs |  0.039744 (prealloc)               |
|     Flecs |  0.014182 (batching)               |
|     Flecs |  0.014090 (batching, prealloc)     |


---
Entity creation, 2 component (n = 1000000):

| Framework | Measurement                        |
|-----------|------------------------------------|
|      EnTT |  0.037106                          |
|      EnTT |  0.073228 (group)                  |
|      EnTT |  0.029022 (prealloc)               |
|      EnTT |  0.032710 (batching)               |
|      EnTT |  0.027097 (batching, prealloc)     |
|      EnTT |  0.058325 (group, batch, prealloc) |
|     Flecs |  0.044280                          |
|     Flecs |  0.038492 (prealloc)               |
|     Flecs |  0.013880 (batching)               |
|     Flecs |  0.014104 (batching, prealloc)     |


---
Entity creation, 3 component (n = 1000000):

| Framework | Measurement                        |
|-----------|------------------------------------|
|      EnTT |  0.058697                          |
|      EnTT |  0.112462 (group)                  |
|      EnTT |  0.055888 (batching)               |
|      EnTT |  0.044004 (prealloc)               |
|      EnTT |  0.043999 (batching, prealloc)     |
|      EnTT |  0.097570 (group, batch, prealloc) |
|     Flecs |  0.048990                          |
|     Flecs |  0.041213 (prealloc)               |
|     Flecs |  0.014088 (batching)               |
|     Flecs |  0.014427 (batching, prealloc)     |


---
Entity deletion, 1 component (n = 1000000):

| Framework | Measurement                        |
|-----------|------------------------------------|
|      EnTT |  0.009142                          |
|     Flecs |  0.036102                          |
|     Flecs |  0.015930 (bulk)                   |


---
Entity deletion, 4 components (n = 1000000):

| Framework | Measurement                        |
|-----------|------------------------------------|
|      EnTT |  0.047977                          |
|      EnTT |  0.088835 (group)                  |
|     Flecs |  0.048018                          |
|     Flecs |  0.016421 (bulk)                   |


---
Entity deletion, 8 components (n = 1000000):

| Framework | Measurement                        |
|-----------|------------------------------------|
|      EnTT |  0.092946                          |
|      EnTT |  0.145475 (group, 4 partial own)   |
|     Flecs |  0.065231                          |
|     Flecs |  0.016967 (bulk)                   |


### Adding & removing components


---
Add one component (n = 1000000):

| Framework | Measurement                        |
|-----------|------------------------------------|
|      EnTT |  0.012633                          |
|     Flecs |  0.033699                          |
|     Flecs |  0.036123 (new w/component)        |
|     Flecs |  0.035498 (add_w_entity)           |
|     Flecs |  0.037122 (tag)                    |
|     Flecs |  0.037628 (switch)                 |
|     Flecs |  0.062016 (existing)               |
|     Flecs |  0.037962 (existing, switch)       |
|     Flecs |  0.066241 (existing w/4)           |
|     Flecs |  0.037554 (existing w/4, switch)   |
|     Flecs |  0.001496 (existing, bulk)         |


---
Add two components (n = 1000000):

| Framework | Measurement                        |
|-----------|------------------------------------|
|      EnTT |  0.024422                          |
|      EnTT |  0.046250 (group)                  |
|     Flecs |  0.092314                          |
|     Flecs |  0.036174 (w/type)                 |
|     Flecs |  0.001480 (to existing, bulk)      |


---
Add three components (n = 1000000):

| Framework | Measurement                        |
|-----------|------------------------------------|
|      EnTT |  0.032891                          |
|      EnTT |  0.074031 (group)                  |
|     Flecs |  0.162656                          |
|     Flecs |  0.039490 (w/type)                 |
|     Flecs |  0.001506 (to existing, bulk)      |


---
Add four components (n = 1000000):

| Framework | Measurement                        |
|-----------|------------------------------------|
|      EnTT |  0.040061                          |
|      EnTT |  0.110185 (group)                  |
|     Flecs |  0.232860                          |
|     Flecs |  0.047324 (w/type)                 |


---
Remove one component (n = 1000000):

| Framework | Measurement                        |
|-----------|------------------------------------|
|      EnTT |  0.006359                          |
|      EnTT |  0.005436 (2 components)           |
|      EnTT |  0.027703 (2 components, group)    |
|     Flecs |  0.035802                          |
|     Flecs |  0.065985 (2 components)           |
|     Flecs |  0.001509 (2 components, bulk)     |


---
Remove two components (n = 1000000):

| Framework | Measurement                        |
|-----------|------------------------------------|
|      EnTT |  0.014914                          |
|      EnTT |  0.037103 (group)                  |
|     Flecs |  0.093782                          |
|     Flecs |  0.039425 (w/type)                 |


---
Remove three components (n = 1000000):

| Framework | Measurement                        |
|-----------|------------------------------------|
|      EnTT |  0.022767                          |
|      EnTT |  0.056071 (group)                  |
|     Flecs |  0.162513                          |
|     Flecs |  0.043412 (w/type)                 |


---
Remove four components (n = 1000000):

| Framework | Measurement                        |
|-----------|------------------------------------|
|      EnTT |  0.039566                          |
|      EnTT |  0.080297 (group)                  |
|     Flecs |  0.237318                          |
|     Flecs |  0.048173 (w/type)                 |


### Iterating over entities with systems


---
Iterate, one component (n = 1000000):

| Framework | Measurement                        |
|-----------|------------------------------------|
|      EnTT |  0.000309 (view)                   |
|     Flecs |  0.000289                          |


---
Iterate, two components (n = 1000000):

| Framework | Measurement                        |
|-----------|------------------------------------|
|      EnTT |  0.001334 (view)                   |
|      EnTT |  0.000446 (group, owning)          |
|     Flecs |  0.000443                          |


---
Iterate, two components, eight types (n = 1000000):

| Framework | Measurement                        |
|-----------|------------------------------------|
|      EnTT |  0.001343 (view)                   |
|      EnTT |  0.000439 (group, owning)          |
|     Flecs |  0.000430                          |


---
Iterate, two components, eight types, four matching (n = 1000000):

| Framework | Measurement                        |
|-----------|------------------------------------|
|      EnTT |  0.002435 (view)                   |
|      EnTT |  0.000438 (group, owning)          |
|     Flecs |  0.000441                          |


---
Iterate, three components (n = 1000000):

| Framework | Measurement                        |
|-----------|------------------------------------|
|      EnTT |  0.001953 (view)                   |
|      EnTT |  0.000685 (group, owning)          |
|     Flecs |  0.000645                          |


---
Iterate, three components, two types (n = 1000000):

| Framework | Measurement                        |
|-----------|------------------------------------|
|      EnTT |  0.001701 (view)                   |
|      EnTT |  0.000685 (group, owning)          |
|     Flecs |  0.000656                          |


---
Iterate, three components, eight types (n = 1000000):

| Framework | Measurement                        |
|-----------|------------------------------------|
|      EnTT |  0.001975 (view)                   |
|      EnTT |  0.000676 (group, owning)          |
|     Flecs |  0.000662                          |


---
Iterate, three components, eight types, four matching (n = 1000000):

| Framework | Measurement                        |
|-----------|------------------------------------|
|      EnTT |  0.003882 (view)                   |
|      EnTT |  0.000681 (group, owning)          |
|     Flecs |  0.000649                          |


---
Iterate, four components, eight types (n = 1000000):

| Framework | Measurement                        |
|-----------|------------------------------------|
|      EnTT |  0.001956 (view)                   |
|      EnTT |  0.000861 (group, owning)          |
|     Flecs |  0.000873                          |


### Ten randomized components


---
Pathological, one component, 1024 types (n = 1000000):

| Framework | Measurement                        |
|-----------|------------------------------------|
|      EnTT |  0.000367 (view)                   |
|     Flecs |  0.000369                          |


---
Pathological, two components, 1024 types (n = 1000000):

| Framework | Measurement                        |
|-----------|------------------------------------|
|      EnTT |  0.001324 (view)                   |
|      EnTT |  0.000446 (group, owning)          |
|     Flecs |  0.000610                          |


---
Pathological, three components, 1024 types (n = 1000000):

| Framework | Measurement                        |
|-----------|------------------------------------|
|      EnTT |  0.001969 (view)                   |
|      EnTT |  0.000674 (group, owning)          |
|     Flecs |  0.000899                          |


---
Pathological, four components, 1024 types (n = 1000000):

| Framework | Measurement                        |
|-----------|------------------------------------|
|      EnTT |  0.003124 (view)                   |
|      EnTT |  0.000872 (group, owning)          |
|     Flecs |  0.001173                          |
