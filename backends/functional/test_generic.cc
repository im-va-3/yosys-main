/*
 *  yosys -- Yosys Open SYnthesis Suite
 *
 *  Copyright (C) 2024  Emily Schmidt <emily@yosyshq.com>
 *  Copyright (C) 2024 National Technology and Engineering Solutions of Sandia, LLC
 *
 *  Permission to use, copy, modify, and/or distribute this software for any
 *  purpose with or without fee is hereby granted, provided that the above
 *  copyright notice and this permission notice appear in all copies.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 *  WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 *  MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 *  ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 *  WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 *  ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 *  OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 *
 */

#include "kernel/yosys.h"
#include "kernel/functional.h"

USING_YOSYS_NAMESPACE
PRIVATE_NAMESPACE_BEGIN

struct FunctionalTestGeneric : public Pass
{
	FunctionalTestGeneric() : Pass("test_generic", "test the generic compute graph") {
		internal();
	}

    void help() override
	{
		//   |---v---|---v---|---v---|---v---|---v---|---v---|---v---|---v---|---v---|---v---|
		log("\n");
		log("TODO: add help message\n");
		log("\n");
    }

	void execute(std::vector<std::string> args, RTLIL::Design *design) override
	{
        log_header(design, "Executing Test Generic.\n");

		size_t argidx = 1;
		extra_args(args, argidx, design);

		for (auto module : design->selected_modules()) {
            log("Dumping module `%s'.\n", module->name);
			auto fir = Functional::IR::from_module(module);
			for(auto node : fir)
				std::cout << node.name().unescape() << " = " << node.to_string([](auto n) { return n.name().unescape(); }) << "\n";
			for(auto output : fir.all_outputs())
				std::cout << output->kind.unescape() << " " << output->name.unescape() << " = " << output->value().name().unescape() << "\n";
			for(auto state : fir.all_states())
				std::cout << state->kind.unescape() << " " << state->name.unescape() << " = " << state->next_value().name().unescape() << "\n";
		}
	}
} FunctionalCxxBackend;

PRIVATE_NAMESPACE_END
