/*
 * ModSecurity, http://www.modsecurity.org/
 * Copyright (c) 2015 - 2020 Trustwave Holdings, Inc. (http://www.trustwave.com/)
 *
 * You may not use this file except in compliance with
 * the License.  You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * If any of the files related to licensing are missing or if you have any
 * other questions related to licensing please contact Trustwave Holdings, Inc.
 * directly using the email address security@modsecurity.org.
 *
 */


#include "src/actions/transformations/parity_zero_7bit.h"

#include <string>

#include "modsecurity/modsecurity.h"
#include "modsecurity/transaction.h"


namespace modsecurity {
namespace actions {
namespace transformations {


void ParityZero7bit::execute(const Transaction *t,
    const ModSecString &in,
    ModSecString &out) noexcept {
    unsigned char *input;

    input = reinterpret_cast<unsigned char *>
        (malloc(sizeof(char) * in.length()+1));

    if (input == NULL) {
        return;
    }

    memcpy(input, in.c_str(), in.length()+1);

    inplace(input, in.length());

    out.assign(reinterpret_cast<char *>(input), in.length());
    free(input);
}


bool ParityZero7bit::inplace(unsigned char *input, uint64_t input_len) {
    uint64_t i;

    i = 0;
    while (i < input_len) {
        input[i] &= 0x7f;
        i++;
    }

    return true;
}


}  // namespace transformations
}  // namespace actions
}  // namespace modsecurity
