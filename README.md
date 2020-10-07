# ECS benchmark

Measurements are per operation. Measurements for bulk operations are scaled to the number of entities. To minimize the impact of scheduling and improve reproducibility, each measurement is done N times, for which the minimum and average time are calculated. The minimum time is the most reproducible, as this is the time with the least impact from the OS scheduler. As the times for most operations are measured in nanoseconds, each measurement measures an operation executed many times (typically 1 million). This minimizes the impact of clock accuracy issues and the overhead of measuring time.

ns = nanoseconds, us = microseconds, ms = milliseconds

Entity creation                 | Min           | Avg
--------------------------------|---------------|--------------
flecs.new_id                    | 9.459 ns      | 11.009 ns
flecs.new_id_recycle            | 2.763 ns      | 3.198 ns
flecs.new_w_entity              | 36.322 ns     | 42.051 ns
flecs.new_1_comp                | 34.001 ns     | 36.739 ns
flecs.new_4_comp                | 41.496 ns     | 48.194 ns
flecs.new_8_comp                | 64.741 ns     | 70.632 ns
flecs.new_16_comp               | 114.135 ns    | 122.362 ns
flecs.bulk_new                  | 6.777 ns      | 7.338 ns
flecs.bulk_new_recycle          | 0.003 ns      | 0.005 ns
flecs.bulk_new_1_comp           | 15.836 ns     | 16.972 ns
flecs.bulk_new_4_comp           | 15.318 ns     | 16.919 ns
flecs.bulk_new_8_comp           | 15.745 ns     | 16.978 ns
flecs.bulk_new_16_comp          | 15.595 ns     | 16.847 ns

Entity deletion                 | Min           | Avg
--------------------------------|---------------|--------------
flecs.delete                    | 22.139 ns     | 23.226 ns
flecs.delete_1_comp             | 44.861 ns     | 48.074 ns
flecs.delete_4_comp             | 58.910 ns     | 63.493 ns
flecs.delete_8_comp             | 92.826 ns     | 97.549 ns
flecs.delete_16_comp            | 159.953 ns    | 170.816 ns
flecs.bulk_delete_1_comp        | 16.858 ns     | 18.274 ns
flecs.bulk_delete_4_comp        | 16.490 ns     | 18.581 ns
flecs.bulk_delete_8_comp        | 17.627 ns     | 19.177 ns
flecs.bulk_delete_16_comp       | 18.384 ns     | 19.884 ns

Adding components               | Min           | Avg
--------------------------------|---------------|--------------
flecs.add_1_comp                | 17.583 ns     | 18.622 ns
flecs.add_4_comp                | 19.521 ns     | 21.870 ns
flecs.add_8_comp                | 24.825 ns     | 27.741 ns
flecs.add_16_comp               | 37.646 ns     | 40.664 ns
flecs.add_to_1_comp             | 54.413 ns     | 57.786 ns
flecs.add_to_4_comp             | 96.484 ns     | 100.129 ns
flecs.add_to_8_comp             | 153.267 ns    | 160.690 ns
flecs.add_to_16_comp            | 298.991 ns    | 321.761 ns
flecs.add_to_1_tag              | 40.855 ns     | 44.008 ns
flecs.add_to_4_tag              | 40.639 ns     | 44.658 ns
flecs.add_to_8_tag              | 40.176 ns     | 43.748 ns
flecs.add_to_16_tag             | 40.493 ns     | 44.813 ns
flecs.add_again                 | 17.990 ns     | 19.225 ns
flecs.bulk_add_to_1             | 1.522 ns      | 1.765 ns
flecs.bulk_add_to_16            | 1.555 ns      | 1.786 ns

Adding case tags                | Min           | Avg
--------------------------------|---------------|--------------
flecs.add_case_to_1_comp        | 39.344 ns     | 41.193 ns
flecs.add_case_to_4_comp        | 40.941 ns     | 42.647 ns
flecs.add_case_to_8_comp        | 39.684 ns     | 42.422 ns
flecs.add_case_to_16_comp       | 41.093 ns     | 42.504 ns

Removing components             | Min           | Avg
--------------------------------|---------------|--------------
flecs.remove_from_1_comp        | 60.830 ns     | 67.320 ns
flecs.remove_from_4_comp        | 103.126 ns    | 109.715 ns
flecs.remove_from_8_comp        | 149.756 ns    | 160.705 ns
flecs.remove_from_16_comp       | 335.079 ns    | 362.004 ns

Setting components              | Min           | Avg
--------------------------------|---------------|--------------
flecs.set                       | 44.842 ns     | 47.119 ns
flecs.set_again                 | 25.977 ns     | 28.495 ns
flecs.set_and_new               | 55.328 ns     | 57.331 ns
flecs.get_mut                   | 18.982 ns     | 19.814 ns
flecs.get_mut_modified          | 27.560 ns     | 30.070 ns

Instancing / Hierachies         | Min           | Avg
--------------------------------|---------------|--------------
flecs.add_instanceof            | 80.083 ns     | 85.735 ns
flecs.add_instanceof_override   | 125.025 ns    | 131.559 ns
flecs.override                  | 89.654 ns     | 94.204 ns
flecs.add_childof               | 78.651 ns     | 87.123 ns

Callbacks                       | Min           | Avg
--------------------------------|---------------|--------------
flecs.set_w_on_set              | 41.370 ns     | 44.009 ns
flecs.add_w_trigger             | 214.818 ns    | 219.544 ns
flecs.add_w_monitor             | 55.932 ns     | 59.054 ns
flecs.add_w_ctor                | 52.505 ns     | 54.721 ns
flecs.remove_w_dtor             | 44.884 ns     | 47.918 ns
flecs.set_w_copy                | 26.518 ns     | 28.107 ns

Getting components              | Min           | Avg
--------------------------------|---------------|--------------
flecs.get_from_single           | 7.460 ns      | 8.328 ns
flecs.get_from_1_comp           | 7.273 ns      | 7.636 ns
flecs.get_from_4_comp           | 8.306 ns      | 8.820 ns
flecs.get_from_8_comp           | 8.865 ns      | 9.410 ns
flecs.get_from_16_comp          | 9.070 ns      | 9.637 ns
flecs.get_ref_from_single       | 2.580 ns      | 2.778 ns
flecs.get_ref_from_1_comp       | 4.563 ns      | 4.913 ns
flecs.get_ref_from_4_comp       | 4.568 ns      | 4.859 ns
flecs.get_ref_from_8_comp       | 4.565 ns      | 5.076 ns
flecs.get_ref_from_16_comp      | 4.491 ns      | 4.929 ns

Has component                   | Min           | Avg
--------------------------------|---------------|--------------
flecs.has_for_1_comp            | 8.542 ns      | 9.493 ns
flecs.has_for_4_comp            | 10.491 ns     | 11.152 ns
flecs.has_for_8_comp            | 11.332 ns     | 12.969 ns
flecs.has_for_16_comp           | 12.282 ns     | 13.056 ns

Misc                            | Min           | Avg
--------------------------------|---------------|--------------
flecs.is_alive_for_alive        | 2.396 ns      | 2.986 ns
flecs.is_alive_for_deleted      | 1.530 ns      | 1.684 ns
flecs.is_alive_for_nonexist     | 0.658 ns      | 0.817 ns
flecs.get_type                  | 3.295 ns      | 3.807 ns
flecs.init_world                | 2.798 ms   | 3.809 ms
flecs.init_mini_world           | 257.360 us   | 339.374 us

Iterate single type             | Min           | Avg
--------------------------------|---------------|--------------
flecs.iter_1m_1comp_1type       | 145.977 us   | 188.943 us
flecs.iter_1m_2comp_1type       | 209.143 us   | 282.193 us
flecs.iter_1m_4comp_1type       | 407.664 us   | 545.868 us

Iterate multiple type           | Min           | Avg
--------------------------------|---------------|--------------
flecs.iter_10k_2comp_1types     | 1.287 us   | 1.624 us
flecs.iter_10k_2comp_2types     | 1.263 us   | 1.708 us
flecs.iter_10k_2comp_64types    | 2.461 us   | 3.180 us
flecs.iter_10k_2comp_256types   | 7.785 us   | 10.427 us

World progress                  | Min           | Avg
--------------------------------|---------------|--------------
flecs.progress_0_sys_user_dt    | 69.374 ns     | 76.137 ns
flecs.progress_0_sys_auto_dt    | 115.902 ns    | 125.194 ns
flecs.progress_1_sys_user_dt    | 126.582 ns    | 128.281 ns
flecs.progress_4_sys_user_dt    | 248.826 ns    | 252.838 ns
flecs.progress_8_sys_user_dt    | 405.778 ns    | 410.441 ns
flecs.progress_16_sys_user_dt   | 707.572 ns    | 719.694 ns