module;

#include "shell/common.hpp"

export module twinning.shell.bridge.library;
import twinning.shell.utility.library;
import twinning.shell.bridge.service;

export namespace Twinning::Shell::Bridge {

	#pragma region type

	class Library {

	protected:

		LibraryLoader m_handle;

		Service * m_symbol;

	public:

		#pragma region constructor

		~Library(
		) {
			if (thiz.state()) {
				thiz.close();
			}
			return;
		}

		// ----------------

		Library(
		) = default;

		Library(
			Library const & that
		) = delete;

		Library(
			Library && that
		) = delete;

		#pragma endregion

		#pragma region operator

		auto operator =(
			Library const & that
		) -> Library & = delete;

		auto operator =(
			Library && that
		) -> Library & = delete;

		#pragma endregion

		#pragma region access

		auto state(
		) -> bool {
			return thiz.m_symbol != nullptr;
		}

		// ----------------

		auto imbue(
			Service * const & symbol
		) -> void {
			assert_test(!thiz.state());
			assert_test(symbol != nullptr);
			try {
				thiz.m_symbol = symbol;
				thiz.m_symbol->initialize();
			}
			catch (...) {
				thiz.m_symbol = nullptr;
				throw;
			}
			return;
		}

		auto open(
			std::string_view const & path
		) -> void {
			assert_test(!thiz.state());
			thiz.m_handle.open(path);
			try {
				thiz.m_symbol = thiz.m_handle.lookup<Service>("_ZN8Twinning6Kernel9Interface7serviceE");
				thiz.m_symbol->initialize();
			}
			catch (...) {
				thiz.m_symbol = nullptr;
				thiz.m_handle.close();
				throw;
			}
			return;
		}

		auto close(
		) -> void {
			assert_test(thiz.state());
			thiz.m_symbol->finalize();
			thiz.m_symbol = nullptr;
			if (thiz.m_handle.state()) {
				thiz.m_handle.close();
			}
			return;
		}

		// ----------------

		auto symbol(
		) -> Service & {
			assert_test(thiz.state());
			return *thiz.m_symbol;
		}

		#pragma endregion

	};

	#pragma endregion

}
