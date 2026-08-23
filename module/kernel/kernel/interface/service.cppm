module;

#include "kernel/common.hpp"

export module twinning.kernel.interface.service;
import twinning.kernel.utility;
import twinning.kernel.interface.data;

export namespace Twinning::Kernel::Interface {

	#pragma region type

	struct Service {

		ZPointer<Executor> executor{nullptr};

		ZPointer<Void ()> initialize{nullptr};

		ZPointer<Void ()> finalize{nullptr};

	};

	#pragma endregion

}
