# ecs_benchmark
ECS benchmark comparison

 * [Creating entities](#creating-entities)
 * [Adding & removing components](#adding-removing-components)
 * [Iterating over entities with systems](#iterating-over-entities-with-systems)
 * [Ten randomized components](#ten-randomized-components)

## Frameworks
 * [EnTT](https://github.com/skypjack/entt)
 * [reflecs](https://github.com/SanderMertens/reflecs)

## Test hardware
The measurements were obtained on a Macbook Pro 2018 model with a 2.6Ghz Intel i7, and 16GB of memory.

## Testing method
Each benchmark is isolated in its own function. Any datastructures required for the test are created during test setup, and teared down after the test has finished. Each benchmark is executed multiple times, and only the lowest measurement is reported. This is done to minimize the impact of scheduling, and to make sure measurements are taken when the data is hot (in the CPU cache).

## Benchmarks

### Creating entities

---
Entity creation, empty (n = 1000000):

| Framework | Measurement                        |
|-----------|------------------------------------|
|      EnTT |  0.001718                          |
|   Reflecs |  0.001868                          |
|      EnTT |  0.001923 (batching)               |
|   Reflecs |  0.000004 (batching)               |


---
Entity creation, 1 component (n = 1000000):

| Framework | Measurement                        |
|-----------|------------------------------------|
|      EnTT |  0.036297                          |
|   Reflecs |  0.024373 (batching)               |


---
Entity creation, 2 component (n = 1000000):

| Framework | Measurement                        |
|-----------|------------------------------------|
|      EnTT |  0.068278                          |
|   Reflecs |  0.014156 (batching, family)       |


---
Entity creation, 3 component (n = 1000000):

| Framework | Measurement                        |
|-----------|------------------------------------|
|      EnTT |  0.095726                          |
|   Reflecs |  0.023933 (batching, family)       |


---
Entity deletion, 1 component (n = 1000000):

| Framework | Measurement                        |
|-----------|------------------------------------|
|      EnTT |  0.008982                          |
|   Reflecs |  0.037047                          |


### Adding & removing components


---
Add one component (n = 1000000):

| Framework | Measurement                        |
|-----------|------------------------------------|
|      EnTT |  0.009538                          |
|   Reflecs |  0.076293                          |
|   Reflecs |  0.070666 (new w/component)        |


---
Add two components (n = 1000000):

| Framework | Measurement                        |
|-----------|------------------------------------|
|      EnTT |  0.040726                          |
|   Reflecs |  0.165913                          |
|   Reflecs |  0.081141 (add w/family)           |


---
Add three components (n = 1000000):

| Framework | Measurement                        |
|-----------|------------------------------------|
|      EnTT |  0.055820                          |
|   Reflecs |  0.298559                          |
|   Reflecs |  0.082781 (add w/family)           |


---
Add four components (n = 1000000):

| Framework | Measurement                        |
|-----------|------------------------------------|
|      EnTT |  0.070472                          |

---
Remove one component (n = 1000000):

| Framework | Measurement                        |
|-----------|------------------------------------|
|      EnTT |  0.005622                          |
|   Reflecs |  0.069068                          |


---
Remove two components (n = 1000000):

| Framework | Measurement                        |
|-----------|------------------------------------|
|      EnTT |  0.012201                          |
|   Reflecs |  0.170163                          |
|   Reflecs |  0.072052 (remove w/family)        |


---
Remove three components (n = 1000000):

| Framework | Measurement                        |
|-----------|------------------------------------|
|      EnTT |  0.023404                          |
|   Reflecs |  0.272413                          |
|   Reflecs |  0.076592 (remove w/family)        |


### Iterating over entities with systems


---
Iterate, one component (n = 1000000):

| Framework | Measurement                        |
|-----------|------------------------------------|
|      EnTT |  0.000508 (view)                   |
|   Reflecs |  0.000457                          |


---
Iterate, two components (n = 1000000):

| Framework | Measurement                        |
|-----------|------------------------------------|
|      EnTT |  0.001581 (view)                   |
|      EnTT |  0.000633 (group, owning)          |
|   Reflecs |  0.000685                          |


---
Iterate, two components, eight types (n = 1000000):

| Framework | Measurement                        |
|-----------|------------------------------------|
|      EnTT |  0.001585 (view)                   |
|      EnTT |  0.000631 (group, owning)          |
|   Reflecs |  0.000627                          |


---
Iterate, two components, eight types, four matching (n = 1000000):

| Framework | Measurement                        |
|-----------|------------------------------------|
|      EnTT |  0.002954 (view)                   |
|      EnTT |  0.000663 (group, owning)          |
|   Reflecs |  0.000616                          |


---
Iterate, three components (n = 1000000):

| Framework | Measurement                        |
|-----------|------------------------------------|
|      EnTT |  0.002287 (view)                   |
|      EnTT |  0.000905 (group, owning)          |
|   Reflecs |  0.000750                          |


---
Iterate, three components, two types (n = 1000000):

| Framework | Measurement                        |
|-----------|------------------------------------|
|      EnTT |  0.002107 (view)                   |
|      EnTT |  0.000965 (group, owning)          |
|   Reflecs |  0.000794                          |


---
Iterate, three components, eight types (n = 1000000):

| Framework | Measurement                        |
|-----------|------------------------------------|
|      EnTT |  0.002336 (view)                   |
|      EnTT |  0.000958 (group, owning)          |
|   Reflecs |  0.000798                          |


---
Iterate, three components, eight types, four matching (n = 1000000):

| Framework | Measurement                        |
|-----------|------------------------------------|
|      EnTT |  0.004407 (view)                   |
|      EnTT |  0.000920 (group, owning)          |
|   Reflecs |  0.000776                          |


---
Iterate, four components, eight types (n = 1000000):

| Framework | Measurement                        |
|-----------|------------------------------------|
|      EnTT |  0.002430 (view)                   |
|      EnTT |  0.001142 (group, owning)          |
|   Reflecs |  0.000956                          |


---
Iterate, four components, eight types, four matching (n = 1000000):

| Framework | Measurement                        |
|-----------|------------------------------------|
|      EnTT |  0.004308 (view)                   |
|      EnTT |  0.001158 (group, owning)          |
|   Reflecs |  0.001047                          |


### Ten randomized components


---
Pathological, one component, 1024 types (n = 1000000):

| Framework | Measurement                        |
|-----------|------------------------------------|
|      EnTT |  0.000409 (view)                   |
|   Reflecs |  0.000530                          |


---
Pathological, two components, 1024 types (n = 1000000):

| Framework | Measurement                        |
|-----------|------------------------------------|
|      EnTT |  0.001597 (view)                   |
|      EnTT |  0.000675 (group, owning)          |
|   Reflecs |  0.000838                          |


---
Pathological, three components, 1024 types (n = 1000000):

| Framework | Measurement                        |
|-----------|------------------------------------|
|      EnTT |  0.002340 (view)                   |
|      EnTT |  0.000903 (group, owning)          |
|   Reflecs |  0.001109                          |


---
Pathological, four components, 1024 types (n = 1000000):

| Framework | Measurement                        |
|-----------|------------------------------------|
|      EnTT |  0.003563 (view)                   |
|      EnTT |  0.001143 (group, owning)          |
|   Reflecs |  0.001388                          |
