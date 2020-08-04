# ecs_benchmark
ECS benchmark comparison

 * [Creating entities](#creating-entities)
 * [Adding & removing components](#adding-removing-components)
 * [Iterating over entities with systems](#iterating-over-entities-with-systems)
 * [Ten randomized components](#ten-randomized-components)

## Frameworks
 * [EnTT](https://github.com/skypjack/entt) (SHA: [fc8e8874a9b29523a5370a959035ee57b7d2be51](https://github.com/skypjack/entt/commit/a95aa81850a3f42ee60ce78c66b2feb1de51dc1e))
 * [flecs](https://github.com/SanderMertens/flecs) (SHA: [2f2d448ae1db7bf3518c202c8e8c6b003947546f](https://github.com/SanderMertens/flecs/commit/612c28635497c1749f8f3e84fa24eabfea58e05))

## Testing hardware
The measurements were obtained on a Macbook Pro 2019 model with a 2.3Ghz Intel i9, and 32GB of memory.

## Testing method
Each benchmark is isolated in its own function. Any datastructures required for the test are created during test setup, and teared down after the test has finished. Each benchmark is executed multiple times, and only the lowest measurement is reported. This is done to minimize the impact of scheduling, and to make sure measurements are taken when the data is hot (in the CPU cache).


## Benchmarks

### Creating entities

---
Entity creation, empty (n = 1000000):

| Framework | Measurement                        |
|-----------|------------------------------------|
|      EnTT |  0.004033                          |
|      EnTT |  0.003019 (batching)               |
|     Flecs |  0.018886                          |
|     Flecs |  0.000003 (batching)               |


---
Entity creation, 1 component (n = 1000000):

| Framework | Measurement                        |
|-----------|------------------------------------|
|      EnTT |  0.021415                          |
|      EnTT |  0.018415 (prealloc)               |
|      EnTT |  0.018844 (batching)               |
|      EnTT |  0.015876 (batching, prealloc)     |
|     Flecs |  0.053130                          |
|     Flecs |  0.031311 (prealloc)               |
|     Flecs |  0.014608 (batching)               |
|     Flecs |  0.007920 (batching, prealloc)     |


---
Entity creation, 2 component (n = 1000000):

| Framework | Measurement                        |
|-----------|------------------------------------|
|      EnTT |  0.040725                          |
|      EnTT |  0.078693 (group)                  |
|      EnTT |  0.031773 (prealloc)               |
|      EnTT |  0.039047 (batching)               |
|      EnTT |  0.030656 (batching, prealloc)     |
|      EnTT |  0.062041 (group, batch, prealloc) |
|     Flecs |  0.054948                          |
|     Flecs |  0.033647 (prealloc)               |
|     Flecs |  0.016582 (batching)               |
|     Flecs |  0.008545 (batching, prealloc)     |


---
Entity creation, 3 component (n = 1000000):

| Framework | Measurement                        |
|-----------|------------------------------------|
|      EnTT |  0.060363                          |
|      EnTT |  0.121950 (group)                  |
|      EnTT |  0.059591 (batching)               |
|      EnTT |  0.052190 (prealloc)               |
|      EnTT |  0.050455 (batching, prealloc)     |
|      EnTT |  0.102582 (group, batch, prealloc) |
|     Flecs |  0.059457                          |
|     Flecs |  0.038622 (prealloc)               |
|     Flecs |  0.016658 (batching)               |
|     Flecs |  0.008669 (batching, prealloc)     |


---
Entity deletion, 1 component (n = 1000000):

| Framework | Measurement                        |
|-----------|------------------------------------|
|      EnTT |  0.009821                          |
|     Flecs |  0.050306                          |
|     Flecs |  0.012000 (bulk)                   |


---
Entity deletion, 4 components (n = 1000000):

| Framework | Measurement                        |
|-----------|------------------------------------|
|      EnTT |  0.048693                          |
|      EnTT |  0.090503 (group)                  |
|     Flecs |  0.062465                          |
|     Flecs |  0.013591 (bulk)                   |


---
Entity deletion, 8 components (n = 1000000):

| Framework | Measurement                        |
|-----------|------------------------------------|
|      EnTT |  0.091692                          |
|      EnTT |  0.142927 (group, 4 full/4 partial own)      |
|     Flecs |  0.095438                          |
|     Flecs |  0.015178 (bulk)                   |


### Adding & removing components


---
Add one component (n = 1000000):

| Framework | Measurement                        |
|-----------|------------------------------------|
|      EnTT |  0.012236                          |
|     Flecs |  0.040675                          |
|     Flecs |  0.032381 (new w/component)        |
|     Flecs |  0.039654 (add_w_entity)           |
|     Flecs |  0.066079 (to existing)            |
|     Flecs |  0.001527 (to existing, bulk)      |


---
Add two components (n = 1000000):

| Framework | Measurement                        |
|-----------|------------------------------------|
|      EnTT |  0.024712                          |
|      EnTT |  0.053221 (group)                  |
|     Flecs |  0.101872                          |
|     Flecs |  0.043744 (w/type)                 |
|     Flecs |  0.001531 (to existing, bulk)      |


---
Add three components (n = 1000000):

| Framework | Measurement                        |
|-----------|------------------------------------|
|      EnTT |  0.035297                          |
|      EnTT |  0.084016 (group)                  |
|     Flecs |  0.171514                          |
|     Flecs |  0.046595 (w/type)                 |
|     Flecs |  0.001542 (to existing, bulk)      |


---
Add four components (n = 1000000):

| Framework | Measurement                        |
|-----------|------------------------------------|
|      EnTT |  0.047670                          |
|      EnTT |  0.116454 (group)                  |
|     Flecs |  0.256227                          |
|     Flecs |  0.074998 (w/type)                 |


---
Remove one component (n = 1000000):

| Framework | Measurement                        |
|-----------|------------------------------------|
|      EnTT |  0.006198                          |
|      EnTT |  0.006054 (2 components)           |
|      EnTT |  0.032139 (2 components, group)    |
|     Flecs |  0.037086                          |
|     Flecs |  0.076840 (2 components)           |
|     Flecs |  0.001523 (2 components, bulk)     |


---
Remove two components (n = 1000000):

| Framework | Measurement                        |
|-----------|------------------------------------|
|      EnTT |  0.015754                          |
|      EnTT |  0.042262 (group)                  |
|     Flecs |  0.094863                          |
|     Flecs |  0.040222 (w/type)                 |


---
Remove three components (n = 1000000):

| Framework | Measurement                        |
|-----------|------------------------------------|
|      EnTT |  0.027408                          |
|      EnTT |  0.058996 (group)                  |
|     Flecs |  0.161452                          |
|     Flecs |  0.044549 (w/type)                 |


---
Remove four components (n = 1000000):

| Framework | Measurement                        |
|-----------|------------------------------------|
|      EnTT |  0.041553                          |
|      EnTT |  0.089692 (group)                  |
|     Flecs |  0.237476                          |
|     Flecs |  0.047159 (w/type)                 |


### Iterating over entities with systems


---
Iterate, one component (n = 1000000):

| Framework | Measurement                        |
|-----------|------------------------------------|
|      EnTT |  0.000300 (view)                   |
|     Flecs |  0.000291                          |


---
Iterate, two components (n = 1000000):

| Framework | Measurement                        |
|-----------|------------------------------------|
|      EnTT |  0.001300 (view)                   |
|      EnTT |  0.000438 (group, owning)          |
|     Flecs |  0.000439                          |


---
Iterate, two components, eight types (n = 1000000):

| Framework | Measurement                        |
|-----------|------------------------------------|
|      EnTT |  0.001317 (view)                   |
|      EnTT |  0.000459 (group, owning)          |
|     Flecs |  0.000441                          |


---
Iterate, two components, eight types, four matching (n = 1000000):

| Framework | Measurement                        |
|-----------|------------------------------------|
|      EnTT |  0.002537 (view)                   |
|      EnTT |  0.000448 (group, owning)          |
|     Flecs |  0.000447                          |

---
Iterate, three components, eight types (n = 1000000):

| Framework | Measurement                        |
|-----------|------------------------------------|
|      EnTT |  0.001943 (view)                   |
|      EnTT |  0.000680 (group, owning)          |
|     Flecs |  0.000649                          |


---
Iterate, three components, eight types, four matching (n = 1000000):

| Framework | Measurement                        |
|-----------|------------------------------------|
|      EnTT |  0.003813 (view)                   |
|      EnTT |  0.000673 (group, owning)          |
|     Flecs |  0.000654                          |


---
Iterate, four components, eight types (n = 1000000):

| Framework | Measurement                        |
|-----------|------------------------------------|
|      EnTT |  0.001982 (view)                   |
|      EnTT |  0.000853 (group, owning)          |
|     Flecs |  0.000894                          |


### Ten randomized components


---
Pathological, one component, 1024 types (n = 1000000):

| Framework | Measurement                        |
|-----------|------------------------------------|
|      EnTT |  0.000302 (view)                   |
|     Flecs |  0.000358                          |


---
Pathological, two components, 1024 types (n = 1000000):

| Framework | Measurement                        |
|-----------|------------------------------------|
|      EnTT |  0.001290 (view)                   |
|      EnTT |  0.000433 (group, owning)          |
|     Flecs |  0.000621                          |


---
Pathological, three components, 1024 types (n = 1000000):

| Framework | Measurement                        |
|-----------|------------------------------------|
|      EnTT |  0.001963 (view)                   |
|      EnTT |  0.000665 (group, owning)          |
|     Flecs |  0.000902                          |


---
Pathological, four components, 1024 types (n = 1000000):

| Framework | Measurement                        |
|-----------|------------------------------------|
|      EnTT |  0.003114 (view)                   |
|      EnTT |  0.000858 (group, owning)          |
|     Flecs |  0.001174                          |
