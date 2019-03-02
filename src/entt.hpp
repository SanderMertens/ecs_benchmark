#include <entt.hpp>

template <typename ...Components, typename Func>
double iterate_view(entt::registry<std::uint64_t> &ecs, int n_iter, Func func) {
    double result = 0;

    for (int i = 0; i < n_iter; i ++) {
        struct timespec start; timespec_gettime(&start);
        ecs.view<Components...>().each(func);
        double t = timespec_measure(&start);
        if (!result || (t < result)) {
            result = t;
        }
    }

    return result;
}

template <typename ...Components, typename Func>
double iterate_group(entt::registry<std::uint64_t> &ecs, int n_iter, Func func) {
    double result = 0;

    for (int i = 0; i < n_iter; i ++) {
        struct timespec start; timespec_gettime(&start);
        ecs.group<Components...>().each(func);
        double t = timespec_measure(&start);
        if (!result || (t < result)) {
            result = t;
        }
    }

    return result;
}

double bench_create_empty_entt(int n) {
    entt::registry<std::uint64_t> ecs;

    struct timespec start; timespec_gettime(&start);
	for (int i = 0; i < n; i++) {
		ecs.create();
	}
    double result = timespec_measure(&start);

    return result;
}

double bench_create_empty_entt_batch(int n) {
    entt::registry<std::uint64_t> ecs;
    std::vector<entt::registry<std::uint64_t>::entity_type> entities(n);

    struct timespec start; timespec_gettime(&start);
    ecs.create(entities.begin(), entities.end());
    double result = timespec_measure(&start);

    return result;
}

double bench_create_1component_entt(int n) {
    entt::registry<std::uint64_t> ecs;

    struct timespec start; timespec_gettime(&start);
	for (int i = 0; i < n; i++) {
		const auto entity = ecs.create();
        ecs.assign<Position>(entity);
	}
    double result = timespec_measure(&start);

    return result;
}

double bench_create_2component_entt(int n) {
    entt::registry<std::uint64_t> ecs;

    struct timespec start; timespec_gettime(&start);
    for(std::uint64_t i = 0; i < n; i++) {
        const auto entity = ecs.create();
        ecs.assign<Position>(entity);
        ecs.assign<Velocity>(entity);
    }
    double result = timespec_measure(&start);

    return result;
}

double bench_create_3component_entt(int n) {
    entt::registry<std::uint64_t> ecs;

    struct timespec start; timespec_gettime(&start);
    for(std::uint64_t i = 0; i < n; i++) {
        const auto entity = ecs.create();
        ecs.assign<Position>(entity);
        ecs.assign<Velocity>(entity);
        ecs.assign<Mass>(entity);
    }
    double result = timespec_measure(&start);

    return result;
}

double bench_delete_1component_entt(int n) {
    entt::registry<std::uint64_t> ecs;

    for(std::uint64_t i = 0; i < n; i++) {
        const auto entity = ecs.create();
        ecs.assign<Position>(entity);
    }

    struct timespec start; timespec_gettime(&start);
    ecs.each([&ecs](auto entity) {
        ecs.destroy(entity);
    });
    double result = timespec_measure(&start);

    return result;
}

double bench_add_one_entt(int n) {
    entt::registry<std::uint64_t> ecs;

	for (int i = 0; i < n; i++) {
		ecs.create();
	}

    struct timespec start; timespec_gettime(&start);
    ecs.each([&ecs](auto entity) {
        ecs.assign<Position>(entity);
    });
    double result = timespec_measure(&start);

    return result;
}

double bench_add_two_entt(int n) {
    entt::registry<std::uint64_t> ecs;

	for (int i = 0; i < n; i++) {
		ecs.create();
	}

    struct timespec start; timespec_gettime(&start);
    ecs.each([&ecs](auto entity) {
        ecs.assign<Position>(entity);
        ecs.assign<Velocity>(entity);
    });
    double result = timespec_measure(&start);

    return result;
}

double bench_add_three_entt(int n) {
    entt::registry<std::uint64_t> ecs;

	for (int i = 0; i < n; i++) {
		ecs.create();
	}

    struct timespec start; timespec_gettime(&start);
    ecs.each([&ecs](auto entity) {
        ecs.assign<Position>(entity);
        ecs.assign<Velocity>(entity);
        ecs.assign<Mass>(entity);
    });
    double result = timespec_measure(&start);

    return result;
}

double bench_add_four_entt(int n) {
    entt::registry<std::uint64_t> ecs;

	for (int i = 0; i < n; i++) {
		ecs.create();
	}

    struct timespec start; timespec_gettime(&start);
    ecs.each([&ecs](auto entity) {
        ecs.assign<Position>(entity);
        ecs.assign<Velocity>(entity);
        ecs.assign<Mass>(entity);
        ecs.assign<Color>(entity);
    });
    double result = timespec_measure(&start);

    return result;
}

double bench_remove_one_entt(int n) {
    entt::registry<std::uint64_t> ecs;

	for (int i = 0; i < n; i++) {
		const auto entity = ecs.create();
        ecs.assign<Position>(entity);
	}

    struct timespec start; timespec_gettime(&start);
    ecs.each([&ecs](auto entity) {
        ecs.remove<Position>(entity);
    });
    double result = timespec_measure(&start);

    return result;
}

double bench_remove_two_entt(int n) {
    entt::registry<std::uint64_t> ecs;

	for (int i = 0; i < n; i++) {
		const auto entity = ecs.create();
        ecs.assign<Position>(entity);
        ecs.assign<Velocity>(entity);
	}

    struct timespec start; timespec_gettime(&start);
    ecs.each([&ecs](auto entity) {
        ecs.remove<Position>(entity);
        ecs.remove<Velocity>(entity);
    });
    double result = timespec_measure(&start);

    return result;
}

double bench_remove_three_entt(int n) {
    entt::registry<std::uint64_t> ecs;

	for (int i = 0; i < n; i++) {
		const auto entity = ecs.create();
        ecs.assign<Position>(entity);
        ecs.assign<Velocity>(entity);
        ecs.assign<Mass>(entity);
	}

    struct timespec start; timespec_gettime(&start);
    ecs.each([&ecs](auto entity) {
        ecs.remove<Position>(entity);
        ecs.remove<Velocity>(entity);
        ecs.remove<Mass>(entity);
    });
    double result = timespec_measure(&start);

    return result;
}

double bench_iter_one_entt_view(int n, int n_iter) {
    entt::registry<std::uint64_t> ecs;

    for(std::uint64_t i = 0; i < n; i++) {
        const auto entity = ecs.create();
        ecs.assign<Position>(entity);
    }

    return iterate_view<Position>(ecs, n_iter, [](auto &p) {
        p.x ++;
        p.y ++;
    });
}

double bench_iter_two_entt_view(int n, int n_iter) {
    entt::registry<std::uint64_t> ecs;

    for(std::uint64_t i = 0; i < n; i++) {
        const auto entity = ecs.create();
        ecs.assign<Position>(entity);
        ecs.assign<Velocity>(entity);
    }

    return iterate_view<Position, Velocity>(ecs, n_iter, [](auto &p, auto &v) {
        p.x += v.x;
        p.y += v.y;
    });
}

double bench_iter_three_two_types_entt_view(int n, int n_iter) {
    entt::registry<std::uint64_t> ecs;

    for(std::uint64_t i = 0; i < n; i++) {
        const auto entity = ecs.create();
        ecs.assign<Position>(entity);
        ecs.assign<Velocity>(entity);
        ecs.assign<Mass>(entity);
        if (i < n / 2) {
            ecs.assign<Rotation>(entity);
        }
    }

    return iterate_view<Position, Velocity, Mass>(ecs, n_iter, [](auto &p, auto &v, auto &m) {
        p.x += v.x;
        p.y += v.y;
    });
}

double bench_iter_two_entt_group(int n, int n_iter) {
    entt::registry<std::uint64_t> ecs;
    ecs.group<Position, Velocity>();

    for(std::uint64_t i = 0; i < n; i++) {
        const auto entity = ecs.create();
        ecs.assign<Position>(entity);
        ecs.assign<Velocity>(entity);
    }

    return iterate_group<Position, Velocity>(ecs, n_iter, [](auto &p, auto &v) {
        p.x += v.x;
        p.y += v.y;
    });
}

double bench_iter_three_two_types_entt_group(int n, int n_iter) {
    entt::registry<std::uint64_t> ecs;

    for(std::uint64_t i = 0; i < n; i++) {
        const auto entity = ecs.create();
        ecs.assign<Position>(entity);
        ecs.assign<Velocity>(entity);
        ecs.assign<Mass>(entity);
        if (i < n / 2) {
            ecs.assign<Rotation>(entity);
        }
    }

    return iterate_group<Position, Velocity, Mass>(ecs, n_iter, [](auto &p, auto &v, auto &m) {
        p.x += v.x / m.value;
        p.y += v.y / m.value;
    });
}

double bench_iter_three_entt_view(int n, int n_iter) {
    entt::registry<std::uint64_t> ecs;

    for(std::uint64_t i = 0; i < n; i++) {
        const auto entity = ecs.create();
        ecs.assign<Position>(entity);
        ecs.assign<Velocity>(entity);
        ecs.assign<Mass>(entity);
    }

    return iterate_view<Position, Velocity, Mass>(ecs, n_iter, [](auto &p, auto &v, auto &m) {
        p.x += v.x / m.value;
        p.y += v.y / m.value;
    });
}

double bench_iter_three_entt_group(int n, int n_iter) {
    entt::registry<std::uint64_t> ecs;
    ecs.group<Position, Velocity, Mass>();

    for(std::uint64_t i = 0; i < n; i++) {
        const auto entity = ecs.create();
        ecs.assign<Position>(entity);
        ecs.assign<Velocity>(entity);
        ecs.assign<Mass>(entity);
    }

    return iterate_group<Position, Velocity, Mass>(ecs, n_iter, [](auto &p, auto &v, auto &m) {
        p.x += v.x / m.value;
        p.y += v.y / m.value;
    });
}

void create_eight_types(entt::registry<std::uint64_t> &ecs, std::uint64_t count, bool match_all) {
    for(std::uint64_t i = 0; i < count; i++) {
        const auto entity = ecs.create();
        ecs.assign<Position>(entity);
        ecs.assign<Mass>(entity);
        ecs.assign<Damage>(entity);
        if ((i % 8) == 1) {
            ecs.assign<Rotation>(entity);
        } else 
        if ((i % 8) == 2) {
            ecs.assign<Color>(entity);
        } else 
        if ((i % 8) == 3) {
            ecs.assign<Battery>(entity);
        } else 
        if ((i % 8) == 4) {
            ecs.assign<Rotation>(entity);
            ecs.assign<Color>(entity);
        } else 
        if ((i % 8) == 5) {
            ecs.assign<Rotation>(entity);
            ecs.assign<Battery>(entity);
        } else 
        if ((i % 8) == 6) {
            ecs.assign<Battery>(entity);
            ecs.assign<Color>(entity);
        } else 
        if ((i % 8) == 7) {
            ecs.assign<Rotation>(entity);
            ecs.assign<Battery>(entity);
            ecs.assign<Color>(entity);
        }

        if (match_all || i % 2) {
            ecs.assign<Velocity>(entity);
        }
    }
}

double bench_iter_two_eight_types_entt_view(int n, int n_iter, bool match_all) {
    entt::registry<std::uint64_t> ecs;

    int count = n * (2 - match_all);

    create_eight_types(ecs, count, match_all);

    return iterate_view<Position, Velocity>(ecs, n_iter, [](auto &p, auto &v) {
        p.x += v.x;
        p.y += v.y;
    });
}

double bench_iter_three_eight_types_entt_view(int n, int n_iter, bool match_all) {
    entt::registry<std::uint64_t> ecs;

    int count = n * (2 - match_all);

    create_eight_types(ecs, count, match_all);

    return iterate_view<Position, Velocity, Mass>(ecs, n_iter, [](auto &p, auto &v, auto &m) {
        p.x += v.x / m.value;
        p.y += v.y / m.value;
    });
}

double bench_iter_two_eight_types_entt_group(int n, int n_iter, bool match_all) {
    entt::registry<std::uint64_t> ecs;
    ecs.group<Position, Velocity, Mass>();

    int count = n * (2 - match_all);

    create_eight_types(ecs, count, match_all);

    return iterate_group<Position, Velocity>(ecs, n_iter, [](auto &p, auto &v) {
        p.x += v.x;
        p.y += v.y;
    });
}

double bench_iter_three_eight_types_entt_group(int n, int n_iter, bool match_all) {
    entt::registry<std::uint64_t> ecs;
    ecs.group<Position, Velocity, Mass>();

    int count = n * (2 - match_all);

    create_eight_types(ecs, count, match_all);

    return iterate_group<Position, Velocity, Mass>(ecs, n_iter, [](auto &p, auto &v, auto &m) {
        p.x += v.x / m.value;
        p.y += v.y / m.value;
    });
}

double bench_iter_four_eight_types_entt_view(int n, int n_iter, bool match_all) {
    entt::registry<std::uint64_t> ecs;

    int count = n * (2 - match_all);

    create_eight_types(ecs, count, match_all);

    return iterate_view<Position, Velocity, Mass>(ecs, n_iter, [](auto &p, auto &v, auto &m) {
        p.x += v.x / m.value;
        p.y += v.y / m.value;
    });
}

double bench_iter_four_eight_types_entt_group(int n, int n_iter, bool match_all) {
    entt::registry<std::uint64_t> ecs;
    ecs.group<Position, Velocity, Mass, Damage>();

    int count = n * (2 - match_all);

    create_eight_types(ecs, count, match_all);

    return iterate_group<Position, Velocity, Mass, Damage>(ecs, n_iter, [](auto &p, auto &v, auto &m, auto &d) {
        p.x += v.x / m.value / d.value;
        p.y += v.y / m.value / d.value;
    });
}

