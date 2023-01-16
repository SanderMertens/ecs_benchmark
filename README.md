# Flecs benchmarks
Keep the following in mind when interpreting the benchmarks:
- To prevent operations from being entirely optimized away by the compiler, the benchmarks have been measured against a shared library/DLL. Performance will be better if Flecs is compiled as part of an application.
- The measurements represent avg/operation, except where this doesn't make sense. For example, the reported time for an `add_remove_16_tags` benchmark should be read as `(add_time + remove_time) / (2 * 16)`.
- Each benchmark runs for a fixed amount of time, and counts how often the benchmarked operations ran in that time.
- The purpose of these benchmarks is to track performance regressions, and to enable others to write and test performance optimizations for Flecs. They intentionally measure as little as possible, and do not reflect real-life scenarios.
- The filter/query iterator tests are evaluated against a dataset with 2^N tables, where N is the reported number of tags/components. The tables are created by randomly adding N components to entities.

## Usage
Use these commands to run the benchmarks:
```bash
# Recursively clean benchmark project and flecs dependency
bake clean -r

# Run benchmarks with optimizations enabled
bake run --cfg release
```

Flecs can be found here:
https://github.com/SanderMertens/flecs

Installation instructions for bake can be found here:
https://github.com/SanderMertens/bake

## Hardware
Benchmarks were measured on a MacBook Pro M1 from 2021, with 64GB RAM

## Benchmarks
ns = nanoseconds, us = microseconds, ms = milliseconds

| Benchmark                           | Measurement |
|-------------------------------------|-------------|
| world_mini_fini                     | 295.63us    |
| world_init_fini                     | 1.22ms      |
| has_empty_entity                    | 1.98ns      |
| has_id_not_found                    | 3.64ns      |
| has_id                              | 4.63ns      |
| has_16_ids                          | 4.91ns      |
| get_empty_entity                    | 1.98ns      |
| get_id_not_found                    | 3.96ns      |
| get_id                              | 4.03ns      |
| get_16_ids                          | 4.21ns      |
| get_pair                            | 4.93ns      |
| get_pair_16_targets                 | 5.17ns      |
| get_mut_id                          | 7.75ns      |
| get_mut_16_ids                      | 8.01ns      |
| set_id                              | 12.19ns     |
| set_16_ids                          | 12.71ns     |
| ref_init                            | 4.63ns      |
| ref_get                             | 2.24ns      |
| add_remove_1_tag                    | 18.43ns     |
| add_remove_2_tags                   | 23.96ns     |
| add_remove_16_tags                  | 29.42ns     |
| add_remove_1_component              | 19.55ns     |
| add_remove_2_components             | 28.10ns     |
| add_remove_16_components            | 84.78ns     |
| add_existing_1_tag                  | 10.25ns     |
| add_existing_16_tags                | 10.54ns     |
| add_existing_1_component            | 10.26ns     |
| add_existing_16_components          | 10.63ns     |
| add_remove_override_1               | 72.10ns     |
| add_remove_override_2               | 76.17ns     |
| add_remove_override_4               | 86.93ns     |
| add_remove_override_16              | 135.08ns    |
| create_delete_empty                 | 5.61ns      |
| create_delete_1_tag                 | 13.57ns     |
| create_delete_2_tags                | 17.62ns     |
| create_delete_16_tags               | 27.08ns     |
| create_delete_1_component           | 14.41ns     |
| create_delete_2_components          | 20.12ns     |
| create_delete_16_components         | 76.35ns     |
| create_delete_tree_depth_1          | 1.12us      |
| create_delete_tree_depth_10         | 8.51us      |
| create_delete_tree_depth_100        | 88.48us     |
| create_delete_tree_depth_1000       | 908.30us    |
| emit_0_observers                    | 23.00ns     |
| emit_1_observer                     | 37.95ns     |
| emit_10_observers                   | 94.42ns     |
| emit_100_observers                  | 732.17ns    |
| emit_propagate_depth_1              | 30.43ns     |
| emit_propagate_depth_10             | 206.13ns    |
| emit_propagate_depth_100            | 2.47us      |
| emit_propagate_depth_1000           | 36.03us     |
| emit_forward_1_ids_depth_1          | 341.35ns    |
| emit_forward_1_ids_depth_1000       | 348.01ns    |
| emit_forward_16_ids_depth_1         | 988.71ns    |
| emit_forward_16_ids_depth_1000      | 996.86ns    |
| modified_0_observers                | 10.26ns     |
| modified_1_observer                 | 50.59ns     |
| modified_10_observers               | 106.16ns    |
| modified_100_observers              | 720.47ns    |
| filter_init_fini_1_ids              | 70.89ns     |
| filter_init_fini_16_ids             | 489.22ns    |
| filter_init_fini_inline_1_ids       | 58.93ns     |
| filter_init_fini_inline_16_ids      | 476.37ns    |
| filter_iter_8_tags_1_term           | 2.39us      |
| filter_iter_8_tags_4_terms          | 4.55us      |
| filter_iter_16_tags_1_term          | 11.18us     |
| filter_iter_16_tags_4_terms         | 22.31us     |
| filter_iter_8_components_1_term     | 2.41us      |
| filter_iter_8_components_4_terms    | 4.61us      |
| filter_iter_16_components_1_term    | 14.06us     |
| filter_iter_16_components_4_terms   | 23.51us     |
| filter_iter_up_8_tags               | 20.64us     |
| filter_iter_up_8_tags_w_self        | 22.58us     |
| query_init_fini_1_ids               | 630.21ns    |
| query_init_fini_16_ids              | 8.55us      |
| query_iter_8_tags_1_term            | 55.18ns     |
| query_iter_8_tags_4_terms           | 55.14ns     |
| query_iter_16_tags_1_term           | 27.73ns     |
| query_iter_16_tags_4_terms          | 27.75ns     |
| query_iter_8_components_1_term      | 56.85ns     |
| query_iter_8_components_4_terms     | 56.75ns     |
| query_iter_16_components_1_term     | 27.82ns     |
| query_iter_16_components_4_terms    | 27.72ns     |
