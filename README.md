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

## Environment
Benchmarks were measured on a MacBook Pro M1 from 2021, with 64GB RAM

Release: https://github.com/SanderMertens/flecs/releases/tag/v3.1.4

## Benchmarks
ns = nanoseconds, us = microseconds, ms = milliseconds

| Benchmark                           | Measurement  |
|-------------------------------------|--------------|
| world_mini_fini                     | 283.96us     |
| world_init_fini                     | 1.10ms       |
| progress_0_systems                  | 86.53ns      |
| progress_1_system                   | 172.26ns     |
| progress_10_systems                 | 520.50ns     |
| progress_100_systems                | 3.90us       |
| has_empty_entity                    | 1.88ns       |
| has_id_not_found                    | 3.13ns       |
| has_id                              | 3.76ns       |
| has_16_ids                          | 4.04ns       |
| get_empty_entity                    | 1.88ns       |
| get_id_not_found                    | 3.75ns       |
| get_id                              | 3.71ns       |
| get_16_ids                          | 3.95ns       |
| get_pair                            | 4.62ns       |
| get_pair_16_targets                 | 4.86ns       |
| get_mut_id                          | 7.53ns       |
| get_mut_16_ids                      | 7.67ns       |
| set_id                              | 11.89ns      |
| set_16_ids                          | 12.34ns      |
| get_mut_remove_id                   | 20.83ns      |
| get_mut_remove_16_ids               | 83.17ns      |
| get_mut_remove_32_ids               | 143.67ns     |
| ref_init                            | 4.68ns       |
| ref_get                             | 2.15ns       |
| add_remove_1_tag                    | 17.54ns      |
| add_remove_2_tags                   | 22.65ns      |
| add_remove_16_tags                  | 27.63ns      |
| add_remove_32_tags                  | 27.81ns      |
| add_remove_1_component              | 18.60ns      |
| add_remove_2_components             | 26.63ns      |
| add_remove_16_components            | 80.29ns      |
| add_remove_32_components            | 138.92ns     |
| add_existing_1_tag                  | 10.06ns      |
| add_existing_16_tags                | 10.35ns      |
| add_existing_1_component            | 10.01ns      |
| add_existing_16_components          | 10.37ns      |
| add_remove_override_1               | 68.86ns      |
| add_remove_override_2               | 73.34ns      |
| add_remove_override_4               | 82.77ns      |
| add_remove_override_16              | 128.91ns     |
| add_remove_cmd_1_tag                | 28.50ns      |
| add_remove_cmd_2_tags               | 23.80ns      |
| add_remove_cmd_16_tags              | 17.54ns      |
| add_remove_cmd_32_tags              | 17.59ns      |
| add_remove_cmd_1_components         | 30.42ns      |
| add_remove_cmd_2_components         | 25.90ns      |
| add_remove_cmd_16_components        | 19.45ns      |
| add_remove_cmd_32_components        | 19.54ns      |
| get_mut_cmd_1                       | 27.86ns      |
| get_mut_cmd_2                       | 22.69ns      |
| get_mut_cmd_16                      | 18.91ns      |
| get_mut_cmd_32                      | 18.82ns      |
| set_cmd_1                           | 40.03ns      |
| set_cmd_2                           | 26.38ns      |
| set_cmd_16                          | 22.15ns      |
| set_cmd_32                          | 22.35ns      |
| get_mut_remove_cmd_1                | 35.83ns      |
| get_mut_remove_cmd_2                | 34.02ns      |
| get_mut_remove_cmd_16               | 27.56ns      |
| get_mut_remove_cmd_32               | 27.11ns      |
| add_remove_hooks_1                  | 21.18ns      |
| add_remove_hooks_2                  | 33.54ns      |
| add_remove_hooks_16                 | 107.03ns     |
| add_remove_hooks_32                 | 179.31ns     |
| create_delete_empty                 | 5.32ns       |
| create_delete_1_tag                 | 12.97ns      |
| create_delete_2_tags                | 16.69ns      |
| create_delete_16_tags               | 25.59ns      |
| create_delete_1_component           | 13.74ns      |
| create_delete_2_components          | 19.06ns      |
| create_delete_16_components         | 72.28ns      |
| create_delete_tree_depth_1          | 1.10us       |
| create_delete_tree_depth_10         | 8.36us       |
| create_delete_tree_depth_100        | 85.28us      |
| create_delete_tree_depth_1000       | 866.11us     |
| emit_0_observers                    | 21.72ns      |
| emit_1_observer                     | 35.83ns      |
| emit_10_observers                   | 89.24ns      |
| emit_100_observers                  | 680.55ns     |
| emit_propagate_depth_1              | 28.62ns      |
| emit_propagate_depth_10             | 195.07ns     |
| emit_propagate_depth_100            | 2.33us       |
| emit_propagate_depth_1000           | 34.13us      |
| emit_forward_1_ids_depth_1          | 298.74ns     |
| emit_forward_1_ids_depth_1000       | 295.39ns     |
| emit_forward_16_ids_depth_1         | 912.10ns     |
| emit_forward_16_ids_depth_1000      | 924.57ns     |
| modified_0_observers                | 9.84ns       |
| modified_1_observer                 | 47.79ns      |
| modified_10_observers               | 100.71ns     |
| modified_100_observers              | 673.34ns     |
| filter_init_fini_1_ids              | 66.98ns      |
| filter_init_fini_16_ids             | 465.44ns     |
| filter_init_fini_inline_1_ids       | 55.78ns      |
| filter_init_fini_inline_16_ids      | 458.48ns     |
| filter_iter_8_tags_1_term           | 2.35us       |
| filter_iter_8_tags_4_terms          | 4.40us       |
| filter_iter_16_tags_1_term          | 10.67us      |
| filter_iter_16_tags_4_terms         | 21.37us      |
| filter_iter_8_components_1_term     | 2.35us       |
| filter_iter_8_components_4_terms    | 4.52us       |
| filter_iter_16_components_1_term    | 13.60us      |
| filter_iter_16_components_4_terms   | 22.10us      |
| filter_iter_up_8_tags               | 47.98us      |
| filter_iter_up_8_tags_w_self        | 46.90us      |
| filter_iter_up_w_mut_8_tags         | 48.26us      |
| filter_iter_up_w_mut_8_tags_w_self  | 47.06us      |
| query_init_fini_1_ids               | 613.76ns     |
| query_init_fini_16_ids              | 8.13us       |
| query_iter_8_tags_1_term            | 52.09ns      |
| query_iter_8_tags_4_terms           | 52.20ns      |
| query_iter_16_tags_1_term           | 26.23ns      |
| query_iter_16_tags_4_terms          | 26.29ns      |
| query_iter_8_components_1_term      | 53.62ns      |
| query_iter_8_components_4_terms     | 53.85ns      |
| query_iter_16_components_1_term     | 26.25ns      |
| query_iter_16_components_4_terms    | 26.24ns      |
