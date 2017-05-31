#pragma once

namespace asset
{
	struct non_copyable
	{
		public:
		non_copyable() = default;
		private:
		non_copyable(const non_copyable&o);
		non_copyable& operator=(const non_copyable&o);
	};
}

