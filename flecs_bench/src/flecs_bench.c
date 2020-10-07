#include "flecs_bench.h"
#include "flecs.h"

ECS_COMPONENT_DECLARE(Comp_A);
ECS_COMPONENT_DECLARE(Comp_B);
ECS_COMPONENT_DECLARE(Comp_C);
ECS_COMPONENT_DECLARE(Comp_D);
ECS_COMPONENT_DECLARE(Comp_E);
ECS_COMPONENT_DECLARE(Comp_F);
ECS_COMPONENT_DECLARE(Comp_G);
ECS_COMPONENT_DECLARE(Comp_H);

ECS_COMPONENT_DECLARE(Comp_I);
ECS_COMPONENT_DECLARE(Comp_J);
ECS_COMPONENT_DECLARE(Comp_K);
ECS_COMPONENT_DECLARE(Comp_L);
ECS_COMPONENT_DECLARE(Comp_M);
ECS_COMPONENT_DECLARE(Comp_N);
ECS_COMPONENT_DECLARE(Comp_O);
ECS_COMPONENT_DECLARE(Comp_P);

ECS_COMPONENT_DECLARE(Comp_Q);

ECS_TAG_DECLARE(Tag_A);
ECS_TAG_DECLARE(Tag_B);
ECS_TAG_DECLARE(Tag_C);
ECS_TAG_DECLARE(Tag_D);
ECS_TAG_DECLARE(Tag_E);
ECS_TAG_DECLARE(Tag_F);
ECS_TAG_DECLARE(Tag_G);
ECS_TAG_DECLARE(Tag_H);

ECS_TAG_DECLARE(Tag_I);
ECS_TAG_DECLARE(Tag_J);
ECS_TAG_DECLARE(Tag_K);
ECS_TAG_DECLARE(Tag_L);
ECS_TAG_DECLARE(Tag_M);
ECS_TAG_DECLARE(Tag_N);
ECS_TAG_DECLARE(Tag_O);
ECS_TAG_DECLARE(Tag_P);

ECS_TYPE_DECLARE(Type1);
ECS_TYPE_DECLARE(Type4);
ECS_TYPE_DECLARE(Type8);
ECS_TYPE_DECLARE(Type16);

ECS_TYPE_DECLARE(Type1_base);
ECS_TYPE_DECLARE(Type4_base);
ECS_TYPE_DECLARE(Type8_base);
ECS_TYPE_DECLARE(Type16_base);

ECS_TYPE_DECLARE(Type1_base_4);
ECS_TYPE_DECLARE(Type4_base_4);
ECS_TYPE_DECLARE(Type8_base_4);
ECS_TYPE_DECLARE(Type16_base_4);

ECS_TYPE_DECLARE(TagType4);
ECS_TYPE_DECLARE(TagType8);
ECS_TYPE_DECLARE(TagType16);

ECS_TYPE_DECLARE(TypeAll);

ECS_CTOR(Comp_A, ptr, {
    ptr->value = 0;
});

ECS_COPY(Comp_A, dst, src, {
    dst->value = src->value;
});

static void Sys_A(ecs_iter_t *it) { }
static void Sys_B(ecs_iter_t *it) { }
static void Sys_C(ecs_iter_t *it) { }
static void Sys_D(ecs_iter_t *it) { }
static void Sys_E(ecs_iter_t *it) { }
static void Sys_F(ecs_iter_t *it) { }
static void Sys_G(ecs_iter_t *it) { }
static void Sys_H(ecs_iter_t *it) { }

static void Sys_I(ecs_iter_t *it) { }
static void Sys_J(ecs_iter_t *it) { }
static void Sys_K(ecs_iter_t *it) { }
static void Sys_L(ecs_iter_t *it) { }
static void Sys_M(ecs_iter_t *it) { }
static void Sys_N(ecs_iter_t *it) { }
static void Sys_O(ecs_iter_t *it) { }
static void Sys_P(ecs_iter_t *it) { }

static
ecs_world_t* world_init() {
    ecs_world_t *w = ecs_init();

    ECS_COMPONENT_DEFINE(w, Comp_A);
    ECS_COMPONENT_DEFINE(w, Comp_B);
    ECS_COMPONENT_DEFINE(w, Comp_C);
    ECS_COMPONENT_DEFINE(w, Comp_D);
    ECS_COMPONENT_DEFINE(w, Comp_E);
    ECS_COMPONENT_DEFINE(w, Comp_F);
    ECS_COMPONENT_DEFINE(w, Comp_G);
    ECS_COMPONENT_DEFINE(w, Comp_H);
    ECS_COMPONENT_DEFINE(w, Comp_I);

    ECS_COMPONENT_DEFINE(w, Comp_J);
    ECS_COMPONENT_DEFINE(w, Comp_K);
    ECS_COMPONENT_DEFINE(w, Comp_L);
    ECS_COMPONENT_DEFINE(w, Comp_M);
    ECS_COMPONENT_DEFINE(w, Comp_N);
    ECS_COMPONENT_DEFINE(w, Comp_O);
    ECS_COMPONENT_DEFINE(w, Comp_P);

    ECS_COMPONENT_DEFINE(w, Comp_Q);

    ECS_TAG_DEFINE(w, Tag_A);
    ECS_TAG_DEFINE(w, Tag_B);
    ECS_TAG_DEFINE(w, Tag_C);
    ECS_TAG_DEFINE(w, Tag_D);
    ECS_TAG_DEFINE(w, Tag_E);
    ECS_TAG_DEFINE(w, Tag_F);
    ECS_TAG_DEFINE(w, Tag_G);
    ECS_TAG_DEFINE(w, Tag_H);

    ECS_TAG_DEFINE(w, Tag_I);
    ECS_TAG_DEFINE(w, Tag_J);
    ECS_TAG_DEFINE(w, Tag_K);
    ECS_TAG_DEFINE(w, Tag_L);
    ECS_TAG_DEFINE(w, Tag_M);
    ECS_TAG_DEFINE(w, Tag_N);
    ECS_TAG_DEFINE(w, Tag_O);
    ECS_TAG_DEFINE(w, Tag_P);

    ECS_ENTITY(w, Base, Comp_Q);
    ECS_ENTITY(w, Base_1, (IsA, Base));
    ECS_ENTITY(w, Base_2, (IsA, Base_1));
    ECS_ENTITY(w, Base_3, (IsA, Base_2));

    ECS_TYPE_DEFINE(w, Type1,  Comp_A);
    ECS_TYPE_DEFINE(w, Type4,  Comp_A, Comp_B, Comp_C, Comp_D);
    ECS_TYPE_DEFINE(w, Type8,  Comp_A, Comp_B, Comp_C, Comp_D, Comp_E, Comp_F, Comp_G, Comp_H);
    ECS_TYPE_DEFINE(w, Type16, Comp_A, Comp_B, Comp_C, Comp_D, Comp_E, Comp_F, Comp_G, Comp_H,
                               Comp_I, Comp_J, Comp_K, Comp_L, Comp_M, Comp_N, Comp_O, Comp_P);

    ECS_TYPE_DEFINE(w, Type1_base, (IsA, Base), Comp_A);
    ECS_TYPE_DEFINE(w, Type4_base, (IsA, Base), Comp_A, Comp_B, Comp_C, Comp_D);
    ECS_TYPE_DEFINE(w, Type8_base, (IsA, Base), Comp_A, Comp_B, Comp_C, Comp_D, Comp_E, Comp_F, Comp_G, Comp_H);
    ECS_TYPE_DEFINE(w, Type16_base, (IsA, Base), Comp_A, Comp_B, Comp_C, Comp_D, Comp_E, Comp_F, Comp_G, Comp_H,
                               Comp_I, Comp_J, Comp_K, Comp_L, Comp_M, Comp_N, Comp_O, Comp_P);

    ECS_TYPE_DEFINE(w, Type1_base_4, (IsA, Base_3), Comp_A);
    ECS_TYPE_DEFINE(w, Type4_base_4, (IsA, Base_3), Comp_A, Comp_B, Comp_C, Comp_D);
    ECS_TYPE_DEFINE(w, Type8_base_4, (IsA, Base_3), Comp_A, Comp_B, Comp_C, Comp_D, Comp_E, Comp_F, Comp_G, Comp_H);
    ECS_TYPE_DEFINE(w, Type16_base_4, (IsA, Base_3), Comp_A, Comp_B, Comp_C, Comp_D, Comp_E, Comp_F, Comp_G, Comp_H,
                               Comp_I, Comp_J, Comp_K, Comp_L, Comp_M, Comp_N, Comp_O, Comp_P);


    ECS_TYPE_DEFINE(w, TagType4,  Tag_A, Tag_B, Tag_C, Tag_D);
    ECS_TYPE_DEFINE(w, TagType8,  Tag_A, Tag_B, Tag_C, Tag_D, Tag_E, Tag_F, Tag_G, Tag_H);
    ECS_TYPE_DEFINE(w, TagType16, Tag_A, Tag_B, Tag_C, Tag_D, Tag_E, Tag_F, Tag_G, Tag_H,
                                  Tag_I, Tag_J, Tag_K, Tag_L, Tag_M, Tag_N, Tag_O, Tag_P);

    ECS_TYPE_DEFINE(w, TypeAll, AND | Type16, AND | TagType16);

    return w;
}

volatile ecs_entity_t ve;

void create_recycled_entities(ecs_world_t *world, int32_t count) {
    const ecs_entity_t *ids_tmp = ecs_bulk_new(world, 0, count);
    ecs_entity_t *ids = malloc(sizeof(ecs_entity_t) * count);
    memcpy(ids, ids_tmp, sizeof(ecs_entity_t) * count);
    for (int i = 0; i < count; i ++) {
        ecs_delete(world, ids[i]);
    }
    ecs_os_free(ids);
}

void flecs_new_id(bench_t b, bench_result_t *b_out) {
    ecs_world_t *world = world_init();

    ecs_dim(world, b.count);

    BENCH_START(b);

    ecs_new_id(world);

    BENCH_STOP(b, b_out);

    ecs_fini(world);
}

void flecs_new_id_recycle(bench_t b, bench_result_t *b_out) {
    ecs_world_t *world = world_init();

    ecs_dim(world, b.count);

    create_recycled_entities(world, b.count);

    BENCH_START(b);

    ecs_new_id(world);

    BENCH_STOP(b, b_out);

    ecs_fini(world);
}

void flecs_new_w_entity(bench_t b, bench_result_t *b_out) {
    ecs_world_t *world = world_init();

    ecs_dim(world, b.count);
    ecs_dim_type(world, ecs_type(Comp_A), b.count);

    BENCH_START(b);
    
    ecs_new_w_entity(world, ecs_typeid(Comp_A));

    BENCH_STOP(b, b_out);

    ecs_fini(world);
}

void flecs_new_1_comp(bench_t b, bench_result_t *b_out) {
    ecs_world_t *world = world_init();

    ecs_dim(world, b.count);
    ecs_dim_type(world, ecs_type(Comp_A), b.count);

    BENCH_START(b);
    
    ecs_new(world, Comp_A);

    BENCH_STOP(b, b_out);

    ecs_fini(world);
}

void flecs_new_n_comp(bench_t b, bench_result_t *b_out, ecs_world_t *world, ecs_type_t type) {
    ecs_dim(world, b.count);
    ecs_dim_type(world, type, b.count);

    BENCH_START(b);
    
    ecs_new_w_type(world, type);

    BENCH_STOP(b, b_out);

    ecs_fini(world);    
}

void flecs_new_4_comp(bench_t b, bench_result_t *b_out) {
    ecs_world_t *world = world_init();
    flecs_new_n_comp(b, b_out, world, ecs_type(Type4));
}

void flecs_new_8_comp(bench_t b, bench_result_t *b_out) {
    ecs_world_t *world = world_init();
    flecs_new_n_comp(b, b_out, world, ecs_type(Type8));
}

void flecs_new_16_comp(bench_t b, bench_result_t *b_out) {
    ecs_world_t *world = world_init();
    flecs_new_n_comp(b, b_out, world, ecs_type(Type16));
}

void flecs_bulk_new(bench_t b, bench_result_t *b_out) {
    ecs_world_t *world = world_init();

    ecs_dim(world, b.count);

    BENCH_START(b);

    ecs_bulk_new(world, 0, b.count);

    BENCH_STOP(b, b_out);

    ecs_fini(world);
}

void flecs_bulk_new_recycle(bench_t b, bench_result_t *b_out) {
    ecs_world_t *world = world_init();

    ecs_dim(world, b.count);

    create_recycled_entities(world, b.count);

    BENCH_START(b);

    ecs_bulk_new(world, 0, b.count);

    BENCH_STOP(b, b_out);

    ecs_fini(world);
}

void flecs_bulk_new_n_comp(bench_t b, bench_result_t *b_out, ecs_world_t *world, ecs_type_t type) {
    ecs_dim(world, b.count);
    ecs_dim_type(world, type, b.count);

    BENCH_START(b);

    ecs_bulk_new_w_type(world, type, b.count);

    BENCH_STOP(b, b_out);

    ecs_fini(world);
}

void flecs_bulk_new_1_comp(bench_t b, bench_result_t *b_out) {
    ecs_world_t *world = world_init();
    flecs_bulk_new_n_comp(b, b_out, world, ecs_type(Comp_A));
}

void flecs_bulk_new_4_comp(bench_t b, bench_result_t *b_out) {
    ecs_world_t *world = world_init();
    flecs_bulk_new_n_comp(b, b_out, world, ecs_type(Type4));
}

void flecs_bulk_new_8_comp(bench_t b, bench_result_t *b_out) {
    ecs_world_t *world = world_init();
    flecs_bulk_new_n_comp(b, b_out, world, ecs_type(Type8));
}

void flecs_bulk_new_16_comp(bench_t b, bench_result_t *b_out) {
    ecs_world_t *world = world_init();
    flecs_bulk_new_n_comp(b, b_out, world, ecs_type(Type16));
}

void flecs_delete_n_comp(bench_t b, bench_result_t *b_out, ecs_world_t *world, ecs_type_t type) {
    ecs_dim(world, b.count);
    if (type) {
        ecs_dim_type(world, type, b.count);
    }

    const ecs_entity_t *ids_tmp = ecs_bulk_new_w_type(world, type, b.count);
    ecs_entity_t *ids = malloc(sizeof(ecs_entity_t) * b.count);
    memcpy(ids, ids_tmp, sizeof(ecs_entity_t) * b.count);

    int e = 0;

    BENCH_START(b);

    ecs_delete(world, ids[e ++]);

    BENCH_STOP(b, b_out);

    ecs_os_free(ids);

    ecs_fini(world);
}

void flecs_delete(bench_t b, bench_result_t *b_out) {
    ecs_world_t *world = world_init();
    flecs_delete_n_comp(b, b_out, world, NULL); 
}

void flecs_delete_1_comp(bench_t b, bench_result_t *b_out) {
    ecs_world_t *world = world_init();
    flecs_delete_n_comp(b, b_out, world, ecs_type(Comp_A));
}

void flecs_delete_4_comp(bench_t b, bench_result_t *b_out) {
    ecs_world_t *world = world_init();
    flecs_delete_n_comp(b, b_out, world, ecs_type(Type4));
}

void flecs_delete_8_comp(bench_t b, bench_result_t *b_out) {
    ecs_world_t *world = world_init();
    flecs_delete_n_comp(b, b_out, world, ecs_type(Type8));
}

void flecs_delete_16_comp(bench_t b, bench_result_t *b_out) {
    ecs_world_t *world = world_init();
    flecs_delete_n_comp(b, b_out, world, ecs_type(Type16));
}

void flecs_bulk_delete_n_comp(bench_t b, bench_result_t *b_out, ecs_world_t *world, ecs_type_t type) {
    ecs_dim(world, b.count);
    if (type) {
        ecs_dim_type(world, type, b.count);
    }

    const ecs_entity_t *ids_tmp = ecs_bulk_new_w_type(world, type, b.count);
    ecs_entity_t *ids = malloc(sizeof(ecs_entity_t) * b.count);
    memcpy(ids, ids_tmp, sizeof(ecs_entity_t) * b.count);

    BENCH_START(b);

    ecs_bulk_delete(world, &(ecs_filter_t){.include = type});

    BENCH_STOP(b, b_out);

    ecs_os_free(ids);

    ecs_fini(world);
}

void flecs_bulk_delete_1_comp(bench_t b, bench_result_t *b_out) {
    ecs_world_t *world = world_init();
    flecs_bulk_delete_n_comp(b, b_out, world, ecs_type(Comp_A));
}

void flecs_bulk_delete_4_comp(bench_t b, bench_result_t *b_out) {
    ecs_world_t *world = world_init();
    flecs_bulk_delete_n_comp(b, b_out, world, ecs_type(Type4));
}

void flecs_bulk_delete_8_comp(bench_t b, bench_result_t *b_out) {
    ecs_world_t *world = world_init();
    flecs_bulk_delete_n_comp(b, b_out, world, ecs_type(Type8));
}

void flecs_bulk_delete_16_comp(bench_t b, bench_result_t *b_out) {
    ecs_world_t *world = world_init();
    flecs_bulk_delete_n_comp(b, b_out, world, ecs_type(Type16));
}

void flecs_add_n_comp(bench_t b, bench_result_t *b_out, ecs_world_t *world, ecs_type_t type) {
    ecs_dim(world, b.count);
    if (type) {
        ecs_dim_type(world, type, b.count);
    }

    const ecs_entity_t *ids_tmp = ecs_bulk_new_w_type(world, NULL, b.count);
    ecs_entity_t *ids = malloc(sizeof(ecs_entity_t) * b.count);
    memcpy(ids, ids_tmp, sizeof(ecs_entity_t) * b.count);

    int e = 0;

    BENCH_START(b);

    ecs_add_type(world, ids[e ++], type);

    BENCH_STOP(b, b_out);

    ecs_os_free(ids);

    ecs_fini(world);
}

void flecs_add_1_comp(bench_t b, bench_result_t *b_out) {
    ecs_world_t *world = world_init();
    flecs_add_n_comp(b, b_out, world, ecs_type(Comp_A));    
}

void flecs_add_4_comp(bench_t b, bench_result_t *b_out) {
    ecs_world_t *world = world_init();
    flecs_add_n_comp(b, b_out, world, ecs_type(Type4));    
}

void flecs_add_8_comp(bench_t b, bench_result_t *b_out) {
    ecs_world_t *world = world_init();
    flecs_add_n_comp(b, b_out, world, ecs_type(Type8));
}

void flecs_add_16_comp(bench_t b, bench_result_t *b_out) {
    ecs_world_t *world = world_init();
    flecs_add_n_comp(b, b_out, world, ecs_type(Type16));
}

void flecs_add_n_comp_no_type(bench_t b, bench_result_t *b_out, ecs_world_t *world, ecs_type_t type) {
    ecs_dim(world, b.count);
    if (type) {
        ecs_dim_type(world, type, b.count);
    }

    const ecs_entity_t *ids_tmp = ecs_bulk_new_w_type(world, NULL, b.count);
    ecs_entity_t *ids = malloc(sizeof(ecs_entity_t) * b.count);
    memcpy(ids, ids_tmp, sizeof(ecs_entity_t) * b.count);

    int e = 0;
    int32_t c, count = ecs_vector_count(type);
    ecs_entity_t *cids = ecs_vector_first(type, ecs_entity_t);

    BENCH_START(b);

    for (c = 0; c < count; c ++) {
        ecs_add_entity(world, ids[e], cids[c]);
    }
    e ++;

    BENCH_STOP(b, b_out);

    ecs_os_free(ids);

    ecs_fini(world);
}

void flecs_add_1_comp_no_type(bench_t b, bench_result_t *b_out) {
    ecs_world_t *world = world_init();
    flecs_add_n_comp_no_type(b, b_out, world, ecs_type(Comp_A));    
}

void flecs_add_4_comp_no_type(bench_t b, bench_result_t *b_out) {
    ecs_world_t *world = world_init();
    flecs_add_n_comp_no_type(b, b_out, world, ecs_type(Type4));    
}

void flecs_add_8_comp_no_type(bench_t b, bench_result_t *b_out) {
    ecs_world_t *world = world_init();
    flecs_add_n_comp_no_type(b, b_out, world, ecs_type(Type8));
}

void flecs_add_16_comp_no_type(bench_t b, bench_result_t *b_out) {
    ecs_world_t *world = world_init();
    flecs_add_n_comp_no_type(b, b_out, world, ecs_type(Type16));
}

void flecs_init_n_comp(bench_t b, bench_result_t *b_out, ecs_world_t *world, ecs_type_t type) {
    ecs_dim(world, b.count);
    if (type) {
        ecs_dim_type(world, type, b.count);
    }

    const ecs_entity_t *ids_tmp = ecs_bulk_new_w_type(world, NULL, b.count);
    ecs_entity_t *ids = malloc(sizeof(ecs_entity_t) * b.count);
    memcpy(ids, ids_tmp, sizeof(ecs_entity_t) * b.count);

    int e = 0;
    int32_t c, count = ecs_vector_count(type);
    ecs_entity_t *cids = ecs_vector_first(type, ecs_entity_t);

    BENCH_START(b);

    ecs_add_type(world, ids[e], type);
    
    for (c = 0; c < count; c ++) {
        Comp_A *ptr = ecs_get_mut_w_entity(world, ids[e], cids[c], NULL);
        ptr->value = 10;
    }

    e ++;

    BENCH_STOP(b, b_out);

    ecs_os_free(ids);

    ecs_fini(world);
}

void flecs_init_1_comp(bench_t b, bench_result_t *b_out) {
    ecs_world_t *world = world_init();
    flecs_init_n_comp(b, b_out, world, ecs_type(Comp_A));    
}

void flecs_init_4_comp(bench_t b, bench_result_t *b_out) {
    ecs_world_t *world = world_init();
    flecs_init_n_comp(b, b_out, world, ecs_type(Type4));    
}

void flecs_init_8_comp(bench_t b, bench_result_t *b_out) {
    ecs_world_t *world = world_init();
    flecs_init_n_comp(b, b_out, world, ecs_type(Type8));
}

void flecs_init_16_comp(bench_t b, bench_result_t *b_out) {
    ecs_world_t *world = world_init();
    flecs_init_n_comp(b, b_out, world, ecs_type(Type16));
}

void flecs_init_n_comp_direct_access(bench_t b, bench_result_t *b_out, ecs_world_t *world, ecs_type_t type) {
    ecs_dim(world, b.count);
    if (type) {
        ecs_dim_type(world, type, b.count);
    }

    int32_t c, count = ecs_vector_count(type);
    ecs_entity_t *components = ecs_vector_first(type, ecs_entity_t);

    ecs_table_t *table = ecs_table_from_type(world, type);
    int32_t *columns = ecs_os_malloc(sizeof(int32_t) * count);
    for (c = 0; c < count; c ++) {
        columns[c] = ecs_table_find_column(table, components[c]);
    }

    BENCH_START(b);

    ecs_entity_t e = ecs_new_id(world);
    ecs_record_t *r = ecs_record_find(world, e);
    ecs_table_insert(world, table, e, r);
    
    for (c = 0; c < count; c ++) {
        Comp_A *ptr = ecs_record_get_column(r, columns[c], sizeof(Comp_A));
        ptr->value = 10;
    }

    BENCH_STOP(b, b_out);

    ecs_os_free(columns);

    ecs_fini(world);
}

void flecs_init_1_comp_direct_access(bench_t b, bench_result_t *b_out) {
    ecs_world_t *world = world_init();
    flecs_init_n_comp_direct_access(b, b_out, world, ecs_type(Comp_A));    
}

void flecs_init_4_comp_direct_access(bench_t b, bench_result_t *b_out) {
    ecs_world_t *world = world_init();
    flecs_init_n_comp_direct_access(b, b_out, world, ecs_type(Type4));    
}

void flecs_init_8_comp_direct_access(bench_t b, bench_result_t *b_out) {
    ecs_world_t *world = world_init();
    flecs_init_n_comp_direct_access(b, b_out, world, ecs_type(Type8));
}

void flecs_init_16_comp_direct_access(bench_t b, bench_result_t *b_out) {
    ecs_world_t *world = world_init();
    flecs_init_n_comp_direct_access(b, b_out, world, ecs_type(Type16));
}

void flecs_bulk_init_n_comp(bench_t b, bench_result_t *b_out, ecs_world_t *world, ecs_type_t type) {
    int32_t c, count = ecs_vector_count(type);
    ecs_entity_t *cids = ecs_vector_first(type, ecs_entity_t);

    void **data = (void**)ecs_os_malloc(sizeof(void*) * count);
    for (c = 0; c < count; c ++) {
        data[c] = ecs_os_calloc(sizeof(Comp_A) * b.count);
    }

    BENCH_START(b);

    ecs_bulk_new_w_data(world, b.count, &(ecs_entities_t){ .count = count, .array = cids}, data);

    BENCH_STOP(b, b_out);

    for (c = 0; c < count; c ++) {
        ecs_os_free(data[c]);
    }    
    ecs_os_free(data);

    ecs_fini(world);
}

void flecs_bulk_init_1_comp(bench_t b, bench_result_t *b_out) {
    ecs_world_t *world = world_init();
    flecs_bulk_init_n_comp(b, b_out, world, ecs_type(Comp_A));    
}

void flecs_bulk_init_4_comp(bench_t b, bench_result_t *b_out) {
    ecs_world_t *world = world_init();
    flecs_bulk_init_n_comp(b, b_out, world, ecs_type(Type4));    
}

void flecs_bulk_init_8_comp(bench_t b, bench_result_t *b_out) {
    ecs_world_t *world = world_init();
    flecs_bulk_init_n_comp(b, b_out, world, ecs_type(Type8));
}

void flecs_bulk_init_16_comp(bench_t b, bench_result_t *b_out) {
    ecs_world_t *world = world_init();
    flecs_bulk_init_n_comp(b, b_out, world, ecs_type(Type16));
}

void flecs_init_n_comp_no_type(bench_t b, bench_result_t *b_out, ecs_world_t *world, ecs_type_t type) {
    ecs_dim(world, b.count);
    if (type) {
        ecs_dim_type(world, type, b.count);
    }

    const ecs_entity_t *ids_tmp = ecs_bulk_new_w_type(world, NULL, b.count);
    ecs_entity_t *ids = malloc(sizeof(ecs_entity_t) * b.count);
    memcpy(ids, ids_tmp, sizeof(ecs_entity_t) * b.count);

    int e = 0;
    int32_t c, count = ecs_vector_count(type);
    ecs_entity_t *cids = ecs_vector_first(type, ecs_entity_t);

    BENCH_START(b);
    
    for (c = 0; c < count; c ++) {
        Comp_A *ptr = ecs_get_mut_w_entity(world, ids[e], cids[c], NULL);
        ptr->value = 10;
    }

    e ++;

    BENCH_STOP(b, b_out);

    ecs_os_free(ids);

    ecs_fini(world);
}

void flecs_init_1_comp_no_type(bench_t b, bench_result_t *b_out) {
    ecs_world_t *world = world_init();
    flecs_init_n_comp_no_type(b, b_out, world, ecs_type(Comp_A));    
}

void flecs_init_4_comp_no_type(bench_t b, bench_result_t *b_out) {
    ecs_world_t *world = world_init();
    flecs_init_n_comp_no_type(b, b_out, world, ecs_type(Type4));    
}

void flecs_init_8_comp_no_type(bench_t b, bench_result_t *b_out) {
    ecs_world_t *world = world_init();
    flecs_init_n_comp_no_type(b, b_out, world, ecs_type(Type8));
}

void flecs_init_16_comp_no_type(bench_t b, bench_result_t *b_out) {
    ecs_world_t *world = world_init();
    flecs_init_n_comp_no_type(b, b_out, world, ecs_type(Type16));
}

void flecs_add_to_n_comp(bench_t b, bench_result_t *b_out, ecs_world_t *world, ecs_type_t type) {
    ecs_type_t prealloc_type = ecs_type_add(world, type, ecs_typeid(Comp_Q));

    ecs_dim(world, b.count);
    ecs_dim_type(world, prealloc_type, b.count);

    const ecs_entity_t *ids_tmp = ecs_bulk_new_w_type(world, type, b.count);
    ecs_entity_t *ids = malloc(sizeof(ecs_entity_t) * b.count);
    memcpy(ids, ids_tmp, sizeof(ecs_entity_t) * b.count);

    int e = 0;

    BENCH_START(b);

    ecs_add(world, ids[e ++], Comp_Q);

    BENCH_STOP(b, b_out);

    ecs_os_free(ids);

    ecs_fini(world);
}

void flecs_add_to_1_comp(bench_t b, bench_result_t *b_out) {
    ecs_world_t *world = world_init();
    flecs_add_to_n_comp(b, b_out, world, ecs_type(Comp_A));    
}

void flecs_add_to_4_comp(bench_t b, bench_result_t *b_out) {
    ecs_world_t *world = world_init();
    flecs_add_to_n_comp(b, b_out, world, ecs_type(Type4));    
}

void flecs_add_to_8_comp(bench_t b, bench_result_t *b_out) {
    ecs_world_t *world = world_init();
    flecs_add_to_n_comp(b, b_out, world, ecs_type(Type8));    
}

void flecs_add_to_16_comp(bench_t b, bench_result_t *b_out) {
    ecs_world_t *world = world_init();
    flecs_add_to_n_comp(b, b_out, world, ecs_type(Type16));    
}

void flecs_add_to_1_tag(bench_t b, bench_result_t *b_out) {
    ecs_world_t *world = world_init();
    flecs_add_to_n_comp(b, b_out, world, ecs_type(Tag_A));    
}

void flecs_add_to_4_tag(bench_t b, bench_result_t *b_out) {
    ecs_world_t *world = world_init();
    flecs_add_to_n_comp(b, b_out, world, ecs_type(TagType4));    
}

void flecs_add_to_8_tag(bench_t b, bench_result_t *b_out) {
    ecs_world_t *world = world_init();
    flecs_add_to_n_comp(b, b_out, world, ecs_type(TagType8));    
}

void flecs_add_to_16_tag(bench_t b, bench_result_t *b_out) {
    ecs_world_t *world = world_init();
    flecs_add_to_n_comp(b, b_out, world, ecs_type(TagType16));    
}

void flecs_add_again(bench_t b, bench_result_t *b_out) {
    ecs_world_t *world = world_init();

    ecs_dim(world, b.count);
    ecs_dim_type(world, ecs_type(Comp_A), b.count);

    const ecs_entity_t *ids_tmp = ecs_bulk_new(world, Comp_A, b.count);
    ecs_entity_t *ids = malloc(sizeof(ecs_entity_t) * b.count);
    memcpy(ids, ids_tmp, sizeof(ecs_entity_t) * b.count);

    int e = 0;

    BENCH_START(b);

    ecs_add(world, ids[e ++], Comp_A);

    BENCH_STOP(b, b_out);

    ecs_os_free(ids);

    ecs_fini(world);
}

void flecs_bulk_add_to_n(bench_t b, bench_result_t *b_out, ecs_world_t *world, ecs_type_t to_add, ecs_type_t type) {
    ecs_dim(world, b.count);
    ecs_dim_type(world, type, b.count);

    const ecs_entity_t *ids_tmp = ecs_bulk_new_w_type(world, type, b.count);
    ecs_entity_t *ids = malloc(sizeof(ecs_entity_t) * b.count);
    memcpy(ids, ids_tmp, sizeof(ecs_entity_t) * b.count);

    BENCH_START(b);

    ecs_bulk_add_type(world, to_add, &(ecs_filter_t){.include = ecs_type(Comp_A)});

    BENCH_STOP(b, b_out);

    ecs_os_free(ids);

    ecs_fini(world);
}

void flecs_bulk_add_to_1(bench_t b, bench_result_t *b_out) {
    ecs_world_t *world = world_init();
    flecs_bulk_add_to_n(b, b_out, world, ecs_type(Comp_Q), ecs_type(Comp_A));
}

void flecs_bulk_add_to_16(bench_t b, bench_result_t *b_out) {
    ecs_world_t *world = world_init();
    flecs_bulk_add_to_n(b, b_out, world, ecs_type(Comp_Q), ecs_type(Type16));
}

void flecs_add_w_trigger(bench_t b, bench_result_t *b_out) {
    ecs_world_t *world = world_init();

    ecs_dim(world, b.count);
    ecs_dim_type(world, ecs_type(Comp_A), b.count);
    
    ECS_TRIGGER(world, Sys_A, EcsOnAdd, Comp_A);

    const ecs_entity_t *ids_tmp = ecs_bulk_new(world, 0, b.count);
    ecs_entity_t *ids = malloc(sizeof(ecs_entity_t) * b.count);
    memcpy(ids, ids_tmp, sizeof(ecs_entity_t) * b.count);

    int e = 0;

    BENCH_START(b);

    ecs_add(world, ids[e ++], Comp_A);

    BENCH_STOP(b, b_out);

    ecs_os_free(ids);

    ecs_fini(world);
}

void flecs_add_w_monitor(bench_t b, bench_result_t *b_out) {
    ecs_world_t *world = world_init();

    ecs_dim(world, b.count);
    ecs_dim_type(world, ecs_type(Comp_A), b.count);
    
    ECS_SYSTEM(world, Sys_A, EcsMonitor, Comp_A);

    const ecs_entity_t *ids_tmp = ecs_bulk_new(world, 0, b.count);
    ecs_entity_t *ids = malloc(sizeof(ecs_entity_t) * b.count);
    memcpy(ids, ids_tmp, sizeof(ecs_entity_t) * b.count);

    int e = 0;

    BENCH_START(b);

    ecs_add(world, ids[e ++], Comp_A);

    BENCH_STOP(b, b_out);

    ecs_os_free(ids);

    ecs_fini(world);
}

void flecs_add_w_ctor(bench_t b, bench_result_t *b_out) {
    ecs_world_t *world = world_init();

    ecs_dim(world, b.count);
    ecs_dim_type(world, ecs_type(Comp_A), b.count);
    
    ecs_set_component_actions(world, Comp_A, {
        .ctor = ecs_ctor(Comp_A)
    });

    const ecs_entity_t *ids_tmp = ecs_bulk_new(world, 0, b.count);
    ecs_entity_t *ids = malloc(sizeof(ecs_entity_t) * b.count);
    memcpy(ids, ids_tmp, sizeof(ecs_entity_t) * b.count);

    int e = 0;

    BENCH_START(b);

    ecs_add(world, ids[e ++], Comp_A);

    BENCH_STOP(b, b_out);

    ecs_os_free(ids);

    ecs_fini(world);
}

void flecs_remove_w_dtor(bench_t b, bench_result_t *b_out) {
    ecs_world_t *world = world_init();

    ecs_dim(world, b.count);
    ecs_dim_type(world, ecs_type(Comp_A), b.count);
    
    ecs_set_component_actions(world, Comp_A, {
        .dtor = ecs_ctor(Comp_A)
    });

    const ecs_entity_t *ids_tmp = ecs_bulk_new(world, Comp_A, b.count);
    ecs_entity_t *ids = malloc(sizeof(ecs_entity_t) * b.count);
    memcpy(ids, ids_tmp, sizeof(ecs_entity_t) * b.count);

    int e = 0;

    BENCH_START(b);

    ecs_remove(world, ids[e ++], Comp_A);

    BENCH_STOP(b, b_out);

    ecs_os_free(ids);

    ecs_fini(world);
}

void flecs_add_case_to_n_comp(bench_t b, bench_result_t *b_out, ecs_world_t *world, ecs_type_t type) {
    ECS_TYPE(world, SwitchType, Tag_A, Tag_B, Tag_C);
    
    ecs_type_t prealloc_type = ecs_type_add(world, type, ECS_SWITCH | SwitchType);
    ecs_dim(world, b.count);
    ecs_dim_type(world, prealloc_type, b.count);

    const ecs_entity_t *ids_tmp = ecs_bulk_new_w_type(world, prealloc_type, b.count);
    ecs_entity_t *ids = malloc(sizeof(ecs_entity_t) * b.count);
    memcpy(ids, ids_tmp, sizeof(ecs_entity_t) * b.count);

    int e = 0;

    BENCH_START(b);

    ecs_add_entity(world, ids[e ++], ECS_CASE | Tag_A);

    BENCH_STOP(b, b_out);

    ecs_os_free(ids);

    ecs_fini(world);
}

void flecs_add_case_to_1_comp(bench_t b, bench_result_t *b_out) {
    ecs_world_t *world = world_init();
    flecs_add_case_to_n_comp(b, b_out, world, ecs_type(Comp_A));    
}

void flecs_add_case_to_4_comp(bench_t b, bench_result_t *b_out) {
    ecs_world_t *world = world_init();
    flecs_add_case_to_n_comp(b, b_out, world, ecs_type(Type4));    
}

void flecs_add_case_to_8_comp(bench_t b, bench_result_t *b_out) {
    ecs_world_t *world = world_init();
    flecs_add_case_to_n_comp(b, b_out, world, ecs_type(Type8));    
}

void flecs_add_case_to_16_comp(bench_t b, bench_result_t *b_out) {
    ecs_world_t *world = world_init();
    flecs_add_case_to_n_comp(b, b_out, world, ecs_type(Type16));    
}

void flecs_add_instanceof(bench_t b, bench_result_t *b_out) {
    ecs_world_t *world = world_init();

    ecs_dim(world, b.count);
    
    ecs_entity_t base = ecs_new(world, Comp_A);

    const ecs_entity_t *ids_tmp = ecs_bulk_new(world, 0, b.count);
    ecs_entity_t *ids = malloc(sizeof(ecs_entity_t) * b.count);
    memcpy(ids, ids_tmp, sizeof(ecs_entity_t) * b.count);

    int e = 0;

    BENCH_START(b);

    ecs_add_entity(world, ids[e ++], ECS_INSTANCEOF | base);

    BENCH_STOP(b, b_out);

    ecs_os_free(ids);

    ecs_fini(world);
}

void flecs_add_instanceof_override(bench_t b, bench_result_t *b_out) {
    ecs_world_t *world = world_init();

    ecs_dim(world, b.count);
    
    ecs_entity_t base = ecs_new(world, Comp_A);
    ecs_add_entity(world, base, ECS_OWNED | ecs_typeid(Comp_A));

    const ecs_entity_t *ids_tmp = ecs_bulk_new(world, 0, b.count);
    ecs_entity_t *ids = malloc(sizeof(ecs_entity_t) * b.count);
    memcpy(ids, ids_tmp, sizeof(ecs_entity_t) * b.count);

    int e = 0;

    BENCH_START(b);

    ecs_add_entity(world, ids[e ++], ECS_INSTANCEOF | base);

    BENCH_STOP(b, b_out);

    ecs_os_free(ids);

    ecs_fini(world);
}

void flecs_override(bench_t b, bench_result_t *b_out) {
    ecs_world_t *world = world_init();

    ecs_dim(world, b.count);
    
    ecs_entity_t base = ecs_new(world, Comp_A);

    const ecs_entity_t *ids_tmp = ecs_bulk_new_w_entity(world, ECS_INSTANCEOF | base, b.count);
    ecs_entity_t *ids = malloc(sizeof(ecs_entity_t) * b.count);
    memcpy(ids, ids_tmp, sizeof(ecs_entity_t) * b.count);

    int e = 0;

    BENCH_START(b);

    ecs_add(world, ids[e ++], Comp_A);

    BENCH_STOP(b, b_out);

    ecs_os_free(ids);

    ecs_fini(world);
}

void flecs_add_childof(bench_t b, bench_result_t *b_out) {
    ecs_world_t *world = world_init();

    ecs_dim(world, b.count);
    
    ecs_entity_t parent = ecs_new(world, Comp_A);

    const ecs_entity_t *ids_tmp = ecs_bulk_new(world, 0, b.count);
    ecs_entity_t *ids = malloc(sizeof(ecs_entity_t) * b.count);
    memcpy(ids, ids_tmp, sizeof(ecs_entity_t) * b.count);

    int e = 0;

    BENCH_START(b);

    ecs_add_entity(world, ids[e ++], ECS_CHILDOF | parent);

    BENCH_STOP(b, b_out);

    ecs_os_free(ids);

    ecs_fini(world);
}

void flecs_add_instanceof_w_child(bench_t b, bench_result_t *b_out) {
    ecs_world_t *world = world_init();

    ecs_dim(world, b.count);
    
    ecs_entity_t base = ecs_new(world, Comp_A);
    ecs_new_w_entity(world, ECS_CHILDOF | base);

    const ecs_entity_t *ids_tmp = ecs_bulk_new(world, 0, b.count);
    ecs_entity_t *ids = malloc(sizeof(ecs_entity_t) * b.count);
    memcpy(ids, ids_tmp, sizeof(ecs_entity_t) * b.count);

    int e = 0;

    BENCH_START(b);

    ecs_add_entity(world, ids[e ++], ECS_INSTANCEOF | base);

    BENCH_STOP(b, b_out);

    ecs_os_free(ids);

    ecs_fini(world);
}

void flecs_remove_from_n_comp(bench_t b, bench_result_t *b_out, ecs_world_t *world, ecs_type_t type) {
    ecs_dim(world, b.count);
    if (type) {
        ecs_dim_type(world, type, b.count);
    }

    const ecs_entity_t *ids_tmp = ecs_bulk_new_w_type(world, type, b.count);
    ecs_entity_t *ids = malloc(sizeof(ecs_entity_t) * b.count);
    memcpy(ids, ids_tmp, sizeof(ecs_entity_t) * b.count);

    int e = 0;

    BENCH_START(b);

    ecs_remove(world, ids[e ++], Comp_Q);

    BENCH_STOP(b, b_out);

    ecs_os_free(ids);

    ecs_fini(world);
}

void flecs_remove_from_1_comp(bench_t b, bench_result_t *b_out) {
    ecs_world_t *world = world_init();
    ECS_TYPE(world, Type, Comp_A, Comp_Q);
    flecs_remove_from_n_comp(b, b_out, world, ecs_type(Type)); 
}

void flecs_remove_from_4_comp(bench_t b, bench_result_t *b_out) {
    ecs_world_t *world = world_init();
    ECS_TYPE(world, Type, Comp_A, Comp_B, Comp_C, Comp_D, Comp_Q);
    flecs_remove_from_n_comp(b, b_out, world, ecs_type(Type)); 
}

void flecs_remove_from_8_comp(bench_t b, bench_result_t *b_out) {
    ecs_world_t *world = world_init();
    ECS_TYPE(world, Type, Comp_A, Comp_B, Comp_C, Comp_D, Comp_E, Comp_F, Comp_G, Comp_Q);
    flecs_remove_from_n_comp(b, b_out, world, ecs_type(Type)); 
}

void flecs_remove_from_16_comp(bench_t b, bench_result_t *b_out) {
    ecs_world_t *world = world_init();
    ECS_TYPE(world, Type, Comp_A, Comp_B, Comp_C, Comp_D, Comp_E, Comp_F, Comp_G, Comp_H,
                          Comp_I, Comp_J, Comp_K, Comp_L, Comp_M, Comp_N, Comp_O, Comp_P, Comp_Q);
    flecs_remove_from_n_comp(b, b_out, world, ecs_type(Type)); 
}

void flecs_set(bench_t b, bench_result_t *b_out) {
    ecs_world_t *world = world_init();

    ecs_dim(world, b.count);
    ecs_dim_type(world, ecs_type(Comp_A), b.count);

    const ecs_entity_t *ids_tmp = ecs_bulk_new(world, 0, b.count);
    ecs_entity_t *ids = malloc(sizeof(ecs_entity_t) * b.count);
    memcpy(ids, ids_tmp, sizeof(ecs_entity_t) * b.count);

    int e = 0;

    BENCH_START(b);

    ecs_set(world, ids[e ++], Comp_A, {10});

    BENCH_STOP(b, b_out);

    ecs_os_free(ids);

    ecs_fini(world);
}

void flecs_set_and_new(bench_t b, bench_result_t *b_out) {
    ecs_world_t *world = world_init();

    ecs_dim(world, b.count);
    ecs_dim_type(world, ecs_type(Comp_A), b.count);

    BENCH_START(b);

    ecs_set(world, 0, Comp_A, {10});

    BENCH_STOP(b, b_out);

    ecs_fini(world);
}

void flecs_set_again(bench_t b, bench_result_t *b_out) {
    ecs_world_t *world = world_init();

    ecs_dim(world, b.count);
    ecs_dim_type(world, ecs_type(Comp_A), b.count);

    const ecs_entity_t *ids_tmp = ecs_bulk_new(world, Comp_A, b.count);
    ecs_entity_t *ids = malloc(sizeof(ecs_entity_t) * b.count);
    memcpy(ids, ids_tmp, sizeof(ecs_entity_t) * b.count);

    int e = 0;

    BENCH_START(b);

    ecs_set(world, ids[e ++], Comp_A, {10});

    BENCH_STOP(b, b_out);

    ecs_os_free(ids);

    ecs_fini(world);
}

void flecs_set_w_on_set(bench_t b, bench_result_t *b_out) {
    ecs_world_t *world = world_init();

    ecs_dim(world, b.count);
    ecs_dim_type(world, ecs_type(Comp_A), b.count);

    ECS_SYSTEM(world, Sys_A, EcsOnSet, Comp_A);

    const ecs_entity_t *ids_tmp = ecs_bulk_new(world, Comp_A, b.count);
    ecs_entity_t *ids = malloc(sizeof(ecs_entity_t) * b.count);
    memcpy(ids, ids_tmp, sizeof(ecs_entity_t) * b.count);

    int e = 0;

    BENCH_START(b);

    ecs_set(world, ids[e ++], Comp_A, {10});

    BENCH_STOP(b, b_out);

    ecs_os_free(ids);

    ecs_fini(world);
}

void flecs_set_w_copy(bench_t b, bench_result_t *b_out) {
    ecs_world_t *world = world_init();

    ecs_dim(world, b.count);
    ecs_dim_type(world, ecs_type(Comp_A), b.count);

    ecs_set_component_actions(world, Comp_A, {
        .ctor = ecs_ctor(Comp_A),
        .copy = ecs_copy(Comp_A)
    });

    const ecs_entity_t *ids_tmp = ecs_bulk_new(world, Comp_A, b.count);
    ecs_entity_t *ids = malloc(sizeof(ecs_entity_t) * b.count);
    memcpy(ids, ids_tmp, sizeof(ecs_entity_t) * b.count);

    int e = 0;

    BENCH_START(b);

    ecs_set(world, ids[e ++], Comp_A, {10});

    BENCH_STOP(b, b_out);

    ecs_os_free(ids);

    ecs_fini(world);
}

void flecs_get_mut(bench_t b, bench_result_t *b_out) {
    ecs_world_t *world = world_init();

    ecs_dim(world, b.count);
    ecs_dim_type(world, ecs_type(Comp_A), b.count);

    const ecs_entity_t *ids_tmp = ecs_bulk_new(world, 0, b.count);
    ecs_entity_t *ids = malloc(sizeof(ecs_entity_t) * b.count);
    memcpy(ids, ids_tmp, sizeof(ecs_entity_t) * b.count);

    int e = 0;

    BENCH_START(b);

    Comp_A *ptr = ecs_get_mut(world, ids[e ++], Comp_A, NULL);
    ptr->value = 10;

    BENCH_STOP(b, b_out);

    ecs_os_free(ids);

    ecs_fini(world);
}

void flecs_get_mut_existing(bench_t b, bench_result_t *b_out) {
    ecs_world_t *world = world_init();

    ecs_dim(world, b.count);
    ecs_dim_type(world, ecs_type(Comp_A), b.count);

    const ecs_entity_t *ids_tmp = ecs_bulk_new(world, Comp_A, b.count);
    ecs_entity_t *ids = malloc(sizeof(ecs_entity_t) * b.count);
    memcpy(ids, ids_tmp, sizeof(ecs_entity_t) * b.count);

    int e = 0;

    BENCH_START(b);

    Comp_A *ptr = ecs_get_mut(world, ids[e ++], Comp_A, NULL);
    ptr->value = 10;

    BENCH_STOP(b, b_out);

    ecs_os_free(ids);

    ecs_fini(world);
}

void flecs_get_mut_modified(bench_t b, bench_result_t *b_out) {
    ecs_world_t *world = world_init();

    ecs_dim(world, b.count);
    ecs_dim_type(world, ecs_type(Comp_A), b.count);

    const ecs_entity_t *ids_tmp = ecs_bulk_new(world, Comp_A, b.count);
    ecs_entity_t *ids = malloc(sizeof(ecs_entity_t) * b.count);
    memcpy(ids, ids_tmp, sizeof(ecs_entity_t) * b.count);

    int e = 0;

    BENCH_START(b);

    Comp_A *ptr = ecs_get_mut(world, ids[e], Comp_A, NULL);
    ptr->value = 10;
    ecs_modified(world, ids[e], Comp_A);

    e ++;

    BENCH_STOP(b, b_out);

    ecs_os_free(ids);

    ecs_fini(world);
}

void flecs_get_from_single(bench_t b, bench_result_t *b_out) {
    ecs_world_t *world = world_init();

    ecs_entity_t e = ecs_set(world, 0, Comp_A, {0});

    BENCH_START(b);

    Comp_A *ptr = (Comp_A*)ecs_get(world, e, Comp_A);

    BENCH_STOP(b, b_out);

    ecs_fini(world);
}

void flecs_get_from_n_comp(bench_t b, bench_result_t *b_out, ecs_world_t *world, ecs_type_t type, ecs_entity_t comp) {
    ecs_dim(world, b.count);
    ecs_dim_type(world, type, b.count);

    ecs_entity_t *ids = malloc(sizeof(ecs_entity_t) * b.count);
    for (int i = 0; i < b.count; i ++) {
        ids[i] = ecs_new_w_type(world, type);
        ecs_set(world, ids[i], Comp_A, {0});
    }

    int e = 0;

    BENCH_START(b);

    Comp_A *ptr = (Comp_A*)ecs_get_id(world, ids[e ++], comp);

    BENCH_STOP(b, b_out);

    ecs_os_free(ids);

    ecs_fini(world);
}


void flecs_get_from_1_comp(bench_t b, bench_result_t *b_out) {
    ecs_world_t *world = world_init();
    flecs_get_from_n_comp(b, b_out, world, ecs_type(Comp_A), ecs_typeid(Comp_A));
}

void flecs_get_from_4_comp(bench_t b, bench_result_t *b_out) {
    ecs_world_t *world = world_init();
    flecs_get_from_n_comp(b, b_out, world, ecs_type(Type4), ecs_typeid(Comp_D));
}

void flecs_get_from_8_comp(bench_t b, bench_result_t *b_out) {
    ecs_world_t *world = world_init();
    flecs_get_from_n_comp(b, b_out, world, ecs_type(Type8), ecs_typeid(Comp_G));
}

void flecs_get_from_16_comp(bench_t b, bench_result_t *b_out) {
    ecs_world_t *world = world_init();
    flecs_get_from_n_comp(b, b_out, world, ecs_type(Type16), ecs_typeid(Comp_P));
}


void flecs_get_from_1_comp_not_found(bench_t b, bench_result_t *b_out) {
    ecs_world_t *world = world_init();
    flecs_get_from_n_comp(b, b_out, world, ecs_type(Comp_A), ecs_typeid(Comp_Q));
}

void flecs_get_from_4_comp_not_found(bench_t b, bench_result_t *b_out) {
    ecs_world_t *world = world_init();
    flecs_get_from_n_comp(b, b_out, world, ecs_type(Type4), ecs_typeid(Comp_Q));
}

void flecs_get_from_8_comp_not_found(bench_t b, bench_result_t *b_out) {
    ecs_world_t *world = world_init();
    flecs_get_from_n_comp(b, b_out, world, ecs_type(Type8), ecs_typeid(Comp_Q));
}

void flecs_get_from_16_comp_not_found(bench_t b, bench_result_t *b_out) {
    ecs_world_t *world = world_init();
    flecs_get_from_n_comp(b, b_out, world, ecs_type(Type16), ecs_typeid(Comp_Q));
}


void flecs_get_from_1_comp_base(bench_t b, bench_result_t *b_out) {
    ecs_world_t *world = world_init();
    flecs_get_from_n_comp(b, b_out, world, ecs_type(Type1_base), ecs_typeid(Comp_Q));
}

void flecs_get_from_4_comp_base(bench_t b, bench_result_t *b_out) {
    ecs_world_t *world = world_init();
    flecs_get_from_n_comp(b, b_out, world, ecs_type(Type4_base), ecs_typeid(Comp_Q));
}

void flecs_get_from_8_comp_base(bench_t b, bench_result_t *b_out) {
    ecs_world_t *world = world_init();
    flecs_get_from_n_comp(b, b_out, world, ecs_type(Type8_base), ecs_typeid(Comp_Q));
}

void flecs_get_from_16_comp_base(bench_t b, bench_result_t *b_out) {
    ecs_world_t *world = world_init();
    flecs_get_from_n_comp(b, b_out, world, ecs_type(Type16_base), ecs_typeid(Comp_Q));
}


void flecs_get_from_1_comp_base_4(bench_t b, bench_result_t *b_out) {
    ecs_world_t *world = world_init();
    flecs_get_from_n_comp(b, b_out, world, ecs_type(Type1_base_4), ecs_typeid(Comp_Q));
}

void flecs_get_from_4_comp_base_4(bench_t b, bench_result_t *b_out) {
    ecs_world_t *world = world_init();
    flecs_get_from_n_comp(b, b_out, world, ecs_type(Type4_base_4), ecs_typeid(Comp_Q));
}

void flecs_get_from_8_comp_base_4(bench_t b, bench_result_t *b_out) {
    ecs_world_t *world = world_init();
    flecs_get_from_n_comp(b, b_out, world, ecs_type(Type8_base_4), ecs_typeid(Comp_Q));
}

void flecs_get_from_16_comp_base_4(bench_t b, bench_result_t *b_out) {
    ecs_world_t *world = world_init();
    flecs_get_from_n_comp(b, b_out, world, ecs_type(Type16_base_4), ecs_typeid(Comp_Q));
}


void flecs_get_ref_from_single(bench_t b, bench_result_t *b_out) {
    ecs_world_t *world = world_init();

    ecs_entity_t e = ecs_set(world, 0, Comp_A, {0});

    ecs_ref_t r = {0};
    ecs_get_ref(world, &r, e, Comp_A);

    BENCH_START(b);

    Comp_A *ptr = (Comp_A*)ecs_get_ref(world, &r, e, Comp_A);

    BENCH_STOP(b, b_out);

    ecs_fini(world);
}

void flecs_get_ref_from_n_comp(bench_t b, bench_result_t *b_out, ecs_world_t *world, ecs_type_t type, ecs_entity_t comp) {
    ecs_dim(world, b.count);
    ecs_dim_type(world, type, b.count);

    ecs_entity_t *ids = malloc(sizeof(ecs_entity_t) * b.count);
    ecs_ref_t *refs = ecs_os_calloc(sizeof(ecs_ref_t) * b.count);

    for (int i = 0; i < b.count; i ++) {
        ids[i] = ecs_new_w_type(world, type);
        ecs_set(world, ids[i], Comp_A, {0});
        ecs_get_ref_w_entity(world, &refs[i], ids[i], comp);
    }

    int e = 0;

    BENCH_START(b);

    Comp_A *ptr = (Comp_A*)ecs_get_ref_w_entity(world, &refs[e], ids[e], comp);
    e ++;

    BENCH_STOP(b, b_out);

    ecs_os_free(ids);
    ecs_os_free(refs);

    ecs_fini(world);
}

void flecs_get_ref_from_1_comp(bench_t b, bench_result_t *b_out) {
    ecs_world_t *world = world_init();
    flecs_get_ref_from_n_comp(b, b_out, world, ecs_type(Comp_A), ecs_typeid(Comp_A));
}

void flecs_get_ref_from_4_comp(bench_t b, bench_result_t *b_out) {
    ecs_world_t *world = world_init();
    flecs_get_ref_from_n_comp(b, b_out, world, ecs_type(Type4), ecs_typeid(Comp_D));
}

void flecs_get_ref_from_8_comp(bench_t b, bench_result_t *b_out) {
    ecs_world_t *world = world_init();
    flecs_get_ref_from_n_comp(b, b_out, world, ecs_type(Type8), ecs_typeid(Comp_G));
}

void flecs_get_ref_from_16_comp(bench_t b, bench_result_t *b_out) {
    ecs_world_t *world = world_init();
    flecs_get_ref_from_n_comp(b, b_out, world, ecs_type(Type16), ecs_typeid(Comp_P));
}

void flecs_has_for_n_comp(bench_t b, bench_result_t *b_out, ecs_world_t *world, ecs_type_t type, ecs_entity_t comp) {
    ecs_dim(world, b.count);
    ecs_dim_type(world, type, b.count);

    const ecs_entity_t *ids = ecs_bulk_new_w_type(world, type, b.count);

    int e = 0;

    BENCH_START(b);

    ecs_has_entity(world, ids[e ++], comp);

    BENCH_STOP(b, b_out);

    ecs_fini(world);
}

void flecs_has_for_1_comp(bench_t b, bench_result_t *b_out) {
    ecs_world_t *world = world_init();
    flecs_has_for_n_comp(b, b_out, world, ecs_type(Comp_A), ecs_typeid(Comp_A));
}

void flecs_has_for_4_comp(bench_t b, bench_result_t *b_out) {
    ecs_world_t *world = world_init();
    flecs_has_for_n_comp(b, b_out, world, ecs_type(Type4), ecs_typeid(Comp_D));
}

void flecs_has_for_8_comp(bench_t b, bench_result_t *b_out) {
    ecs_world_t *world = world_init();
    flecs_has_for_n_comp(b, b_out, world, ecs_type(Type8), ecs_typeid(Comp_G));
}

void flecs_has_for_16_comp(bench_t b, bench_result_t *b_out) {
    ecs_world_t *world = world_init();
    flecs_has_for_n_comp(b, b_out, world, ecs_type(Type16), ecs_typeid(Comp_P));
}

void flecs_is_alive_for_alive(bench_t b, bench_result_t *b_out) {
    ecs_world_t *world = world_init();

    const ecs_entity_t *ids = ecs_bulk_new(world, Comp_A, b.count);
    int e = 0;

    BENCH_START(b);

    ecs_is_alive(world, ids[e ++]);

    BENCH_STOP(b, b_out);

    ecs_fini(world);
}

void flecs_is_alive_for_deleted(bench_t b, bench_result_t *b_out) {
    ecs_world_t *world = world_init();

    const ecs_entity_t *ids_tmp = ecs_bulk_new(world, Comp_A, b.count);
    ecs_entity_t *ids = malloc(sizeof(ecs_entity_t) * b.count);
    memcpy(ids, ids_tmp, sizeof(ecs_entity_t) * b.count);

    for (int i = 0; i < b.count; i ++) {
        ecs_delete(world, ids[i]);
    }

    int e = 0;

    BENCH_START(b);

    ecs_is_alive(world, ids[e ++]);

    BENCH_STOP(b, b_out);

    ecs_fini(world);
}

void flecs_is_alive_for_nonexist(bench_t b, bench_result_t *b_out) {
    ecs_world_t *world = world_init();

    BENCH_START(b);

    ecs_is_alive(world, 5000);

    BENCH_STOP(b, b_out);

    ecs_fini(world);
}

void flecs_get_type(bench_t b, bench_result_t *b_out) {
    ecs_world_t *world = world_init();

    const ecs_entity_t *ids = ecs_bulk_new(world, Comp_A, b.count);
    int e = 0;

    BENCH_START(b);

    ecs_get_type(world, ids[e ++]);

    BENCH_STOP(b, b_out);

    ecs_fini(world);
}

void flecs_init_world(bench_t b, bench_result_t *b_out) {
    ecs_world_t *w = NULL;

    BENCH_START(b);

    w = ecs_init(); // should loop only once

    BENCH_STOP(b, b_out);

    if (w) ecs_fini(w);
}

void flecs_init_mini_world(bench_t b, bench_result_t *b_out) {
    ecs_world_t *w = NULL;

    BENCH_START(b);

    w = ecs_mini(); // should loop only once

    BENCH_STOP(b, b_out);

    if (w) ecs_fini(w);
}

void flecs_iter_1m_1comp_1type(bench_t b, bench_result_t *b_out) {
    ecs_world_t *world = world_init();

    ecs_set_component_actions(world, Comp_A, {
        .ctor = ecs_ctor(Comp_A)
    });

    ecs_bulk_new(world, Comp_A, 1000000);

    ecs_query_t *q = ecs_query_new(world, "Comp_A");

    BENCH_START(b);

    ecs_iter_t it = ecs_query_iter(q);
    while (ecs_query_next(&it)) {
        Comp_A *ptr = ecs_column(&it, Comp_A, 1);
        for (int i = 0; i < it.count; i ++) {
            ptr[i].value ++;
        }
    }

    BENCH_STOP(b, b_out);

    ecs_fini(world);
}

void flecs_iter_1m_2comp_1type(bench_t b, bench_result_t *b_out) {
    ecs_world_t *world = world_init();

    ecs_set_component_actions(world, Comp_A, {
        .ctor = ecs_ctor(Comp_A)
    });
    ecs_set_component_actions(world, Comp_B, {
        .ctor = ecs_ctor(Comp_A)
    });    

    ECS_TYPE(world, Type, Comp_A, Comp_B);

    ecs_bulk_new(world, Type, 1000000);

    ecs_query_t *q = ecs_query_new(world, "Comp_A, Comp_B");

    BENCH_START(b);

    ecs_iter_t it = ecs_query_iter(q);
    while (ecs_query_next(&it)) {
        Comp_A *ptr_a = ecs_column(&it, Comp_A, 1);
        Comp_B *ptr_b = ecs_column(&it, Comp_B, 2);

        for (int i = 0; i < it.count; i ++) {
            ptr_a[i].value += ptr_b[i].value;
        }
    }

    BENCH_STOP(b, b_out);

    ecs_fini(world);
}

void flecs_iter_1m_4comp_1type(bench_t b, bench_result_t *b_out) {
    ecs_world_t *world = world_init();

    ecs_set_component_actions(world, Comp_A, { .ctor = ecs_ctor(Comp_A) });
    ecs_set_component_actions(world, Comp_B, { .ctor = ecs_ctor(Comp_A) }); 
    ecs_set_component_actions(world, Comp_C, { .ctor = ecs_ctor(Comp_A) }); 
    ecs_set_component_actions(world, Comp_D, { .ctor = ecs_ctor(Comp_A) });

    ECS_TYPE(world, Type, Comp_A, Comp_B, Comp_C, Comp_D);

    ecs_bulk_new(world, Type, 1000000);

    ecs_query_t *q = ecs_query_new(world, "Comp_A, Comp_B, Comp_C, Comp_D");

    BENCH_START(b);

    ecs_iter_t it = ecs_query_iter(q);
    while (ecs_query_next(&it)) {
        Comp_A *ptr_a = ecs_column(&it, Comp_A, 1);
        Comp_B *ptr_b = ecs_column(&it, Comp_B, 2);
        Comp_C *ptr_c = ecs_column(&it, Comp_C, 3);
        Comp_D *ptr_d = ecs_column(&it, Comp_D, 4);

        for (int i = 0; i < it.count; i ++) {
            ptr_a[i].value += ptr_b[i].value + ptr_c[i].value + ptr_d[i].value;
        }
    }

    BENCH_STOP(b, b_out);

    ecs_fini(world);
}

void flecs_iter_10k_2comp_ntypes(bench_t b, bench_result_t *b_out, int types) {
    ecs_world_t *world = world_init();

    ecs_set_component_actions(world, Comp_A, {
        .ctor = ecs_ctor(Comp_A)
    });
    ecs_set_component_actions(world, Comp_B, {
        .ctor = ecs_ctor(Comp_A)
    });    

    ECS_TYPE(world, Type, Comp_A, Comp_B);

    const ecs_entity_t *ids = ecs_bulk_new(world, 0, 10000);
    ecs_entity_t tag = 5000000; // Some id that won't be overwritten by anything
    for (int i = 0; i < 10000; i ++) {
        ecs_add_entity(world, ids[i], tag + (i % types));
    }
    for (int i = 0; i < 10000; i ++) {
        ecs_add(world, ids[i], Type);
    }

    ecs_query_t *q = ecs_query_new(world, "Comp_A, Comp_B");

    BENCH_START(b);

    ecs_iter_t it = ecs_query_iter(q);
    while (ecs_query_next(&it)) {
        Comp_A *ptr_a = ecs_column(&it, Comp_A, 1);
        Comp_B *ptr_b = ecs_column(&it, Comp_B, 2);

        for (int i = 0; i < it.count; i ++) {
            ptr_a[i].value += ptr_b[i].value;
        }
    }

    BENCH_STOP(b, b_out);

    ecs_fini(world);
}

void flecs_iter_10k_2comp_1types(bench_t b, bench_result_t *b_out) {
    flecs_iter_10k_2comp_ntypes(b, b_out, 1);
}

void flecs_iter_10k_2comp_2types(bench_t b, bench_result_t *b_out) {
    flecs_iter_10k_2comp_ntypes(b, b_out, 2);
}

void flecs_iter_10k_2comp_64types(bench_t b, bench_result_t *b_out) {
    flecs_iter_10k_2comp_ntypes(b, b_out, 64);
}

void flecs_iter_10k_2comp_256types(bench_t b, bench_result_t *b_out) {
    flecs_iter_10k_2comp_ntypes(b, b_out, 256);
}

void flecs_progress_0_sys_user_dt(bench_t b, bench_result_t *b_out) {
    ecs_world_t *world = world_init();

    // Run progress once so that pipeline is initialized
    ecs_progress(world, 1);

    BENCH_START(b);

    ecs_progress(world, 1);

    BENCH_STOP(b, b_out);

    ecs_fini(world);
}

void flecs_progress_0_sys_auto_dt(bench_t b, bench_result_t *b_out) {
    ecs_world_t *world = world_init();

    // Run progress once so that pipeline is initialized
    ecs_progress(world, 1);

    BENCH_START(b);

    ecs_progress(world, 0);

    BENCH_STOP(b, b_out);

    ecs_fini(world);
}

void flecs_progress_1_sys_user_dt(bench_t b, bench_result_t *b_out) {
    ecs_world_t *world = world_init();

    ECS_SYSTEM(world, Sys_A, EcsOnUpdate, Comp_A);
    ecs_new(world, Comp_A);

    // Run progress once so that pipeline is initialized
    ecs_progress(world, 1);

    BENCH_START(b);

    ecs_progress(world, 1);

    BENCH_STOP(b, b_out);

    ecs_fini(world);
}

void flecs_progress_4_sys_user_dt(bench_t b, bench_result_t *b_out) {
    ecs_world_t *world = world_init();

    ECS_SYSTEM(world, Sys_A, EcsOnUpdate, Comp_A);
    ECS_SYSTEM(world, Sys_B, EcsOnUpdate, Comp_A);
    ECS_SYSTEM(world, Sys_C, EcsOnUpdate, Comp_A);
    ECS_SYSTEM(world, Sys_D, EcsOnUpdate, Comp_A);
    ecs_new(world, Comp_A);

    // Run progress once so that pipeline is initialized
    ecs_progress(world, 1);

    BENCH_START(b);

    ecs_progress(world, 1);

    BENCH_STOP(b, b_out);

    ecs_fini(world);
}

void flecs_progress_8_sys_user_dt(bench_t b, bench_result_t *b_out) {
    ecs_world_t *world = world_init();

    ECS_SYSTEM(world, Sys_A, EcsOnUpdate, Comp_A);
    ECS_SYSTEM(world, Sys_B, EcsOnUpdate, Comp_A);
    ECS_SYSTEM(world, Sys_C, EcsOnUpdate, Comp_A);
    ECS_SYSTEM(world, Sys_D, EcsOnUpdate, Comp_A);
    ECS_SYSTEM(world, Sys_E, EcsOnUpdate, Comp_A);
    ECS_SYSTEM(world, Sys_F, EcsOnUpdate, Comp_A);
    ECS_SYSTEM(world, Sys_G, EcsOnUpdate, Comp_A);
    ECS_SYSTEM(world, Sys_H, EcsOnUpdate, Comp_A);
    ecs_new(world, Comp_A);

    // Run progress once so that pipeline is initialized
    ecs_progress(world, 1);

    BENCH_START(b);

    ecs_progress(world, 1);

    BENCH_STOP(b, b_out);

    ecs_fini(world);
}

void flecs_progress_16_sys_user_dt(bench_t b, bench_result_t *b_out) {
    ecs_world_t *world = world_init();

    ECS_SYSTEM(world, Sys_A, EcsOnUpdate, Comp_A);
    ECS_SYSTEM(world, Sys_B, EcsOnUpdate, Comp_A);
    ECS_SYSTEM(world, Sys_C, EcsOnUpdate, Comp_A);
    ECS_SYSTEM(world, Sys_D, EcsOnUpdate, Comp_A);
    ECS_SYSTEM(world, Sys_E, EcsOnUpdate, Comp_A);
    ECS_SYSTEM(world, Sys_F, EcsOnUpdate, Comp_A);
    ECS_SYSTEM(world, Sys_G, EcsOnUpdate, Comp_A);
    ECS_SYSTEM(world, Sys_H, EcsOnUpdate, Comp_A);

    ECS_SYSTEM(world, Sys_I, EcsOnUpdate, Comp_A);
    ECS_SYSTEM(world, Sys_J, EcsOnUpdate, Comp_A);
    ECS_SYSTEM(world, Sys_K, EcsOnUpdate, Comp_A);
    ECS_SYSTEM(world, Sys_L, EcsOnUpdate, Comp_A);
    ECS_SYSTEM(world, Sys_M, EcsOnUpdate, Comp_A);
    ECS_SYSTEM(world, Sys_N, EcsOnUpdate, Comp_A);
    ECS_SYSTEM(world, Sys_O, EcsOnUpdate, Comp_A);
    ECS_SYSTEM(world, Sys_P, EcsOnUpdate, Comp_A);    
    ecs_new(world, Comp_A);

    // Run progress once so that pipeline is initialized
    ecs_progress(world, 1);

    BENCH_START(b);

    ecs_progress(world, 1);

    BENCH_STOP(b, b_out);

    ecs_fini(world);
}
