#pragma once
#include "bigint.h"
#include "board.h"
#include "fact.h"
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

typedef __gnu_pbds::tree<int, __gnu_pbds::null_type, std::less<int>, __gnu_pbds::rb_tree_tag, __gnu_pbds::tree_order_statistics_node_update> ordered_set;

template <int N>
void board_hash(const Board<N> &board, BigInt &result);
