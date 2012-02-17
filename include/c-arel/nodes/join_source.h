/*
 * Copyright (C) 2012 Joshua Hollenbeck
 *
 * This file is part of c-arel, distributed under the MIT-LICENSE.
 * For full terms see the included MIT-LICENSE file.
 */

#ifndef include_c_arel_join_source_h
#define include_c_arel_join_source_h
namespace c_arel {
  namespace nodes {
    //////
    // Class that represents a join source
    //
    //   http://www.sqlite.org/syntaxdiagrams.html#join-source
    class JoinSource : public Binary {
    public:
      explicit JoinSource(Table *single_source);
      explicit JoinSource(Table *single_source, variant joinop);

      bool isEmpty(void);

      // inheritance/rtii support
      virtual variant self(void) { return *this; }
      virtual const char *classname(void);
    };
  }
}
#endif
