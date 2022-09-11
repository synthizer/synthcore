/**
 * This file includes all the headers, which makes sure that we at least get basic validation that the library can
 * build.
 * */

#include "synthcore/at_scope_exit.hpp"
#include "synthcore/block_delay_line.hpp"
#include "synthcore/cells.hpp"
#include "synthcore/channel_mixing.hpp"
#include "synthcore/compiler_specifics.hpp"
#include "synthcore/config.hpp"
#include "synthcore/data/arrays.hpp"
#include "synthcore/edge_trigger.hpp"
#include "synthcore/fade_driver.hpp"
#include "synthcore/faders.hpp"
#include "synthcore/fast_sine_bank.hpp"
#include "synthcore/filter_design.hpp"
#include "synthcore/generation_thread.hpp"
#include "synthcore/generic_timeline.hpp"
#include "synthcore/iir_filter.hpp"
#include "synthcore/interpolated_random_sequence.hpp"
#include "synthcore/math.hpp"
#include "synthcore/mod_pointer.hpp"
#include "synthcore/mpsc_ring.hpp"
#include "synthcore/noise_generator.hpp"
#include "synthcore/prime_helpers.hpp"
#include "synthcore/random_generator.hpp"
#include "synthcore/small_vec.hpp"
#include "synthcore/spsc_ring.hpp"
#include "synthcore/three_band_eq.hpp"
#include "synthcore/trylock.hpp"
#include "synthcore/types.hpp"
#include "synthcore/vbool.hpp"
#include "synthcore/vector_helpers.hpp"
#include "synthcore/xoshiro.hpp"
