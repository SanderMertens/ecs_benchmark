/*
                                   )
                                  (.)
                                  .|.
                                  | |
                              _.--| |--._
                           .-';  ;`-'& ; `&.
                          \   &  ;    &   &_/
                           |"""---...---"""|
                           \ | | | | | | | /
                            `---.|.|.|.---'

 * This file is generated by bake.lang.c for your convenience. Headers of
 * dependencies will automatically show up in this file. Include bake_config.h
 * in your main project file. Do not edit! */

#ifndef BENCH_COMMON_BAKE_CONFIG_H
#define BENCH_COMMON_BAKE_CONFIG_H

/* Headers of public dependencies */
/* No dependencies */

/* Convenience macro for exporting symbols */
#ifndef bench_common_STATIC
#if bench_common_EXPORTS && (defined(_MSC_VER) || defined(__MINGW32__))
  #define BENCH_COMMON_EXPORT __declspec(dllexport)
#elif bench_common_EXPORTS
  #define BENCH_COMMON_EXPORT __attribute__((__visibility__("default")))
#elif defined _MSC_VER
  #define BENCH_COMMON_EXPORT __declspec(dllimport)
#else
  #define BENCH_COMMON_EXPORT
#endif
#else
  #define BENCH_COMMON_EXPORT
#endif

#endif

