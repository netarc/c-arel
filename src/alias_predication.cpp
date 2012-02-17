/*
 * Copyright (C) 2012 Joshua Hollenbeck
 *
 * This file is part of c-arel, distributed under the MIT-LICENSE.
 * For full terms see the included MIT-LICENSE file.
 */

#include "c-arel.h"

namespace c_arel {
  nodes::As AliasPredication::as(const char *other) {
    return nodes::As(self(), nodes::SqlLiteral(other));
  }
}