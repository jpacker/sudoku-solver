namespace meta
{
	inline constexpr std::size_t sqrt_impl
		(
		 std::size_t n, 
		 std::size_t low, 
		 std::size_t high
		)
	{
		if(low == high)
		{
			return low;
		}
		
		const auto mid = (low + high) / 2;
		if(mid*mid >= n)
		{
			return sqrt_impl(n, low, mid);
		}
		else
		{
			return sqrt_impl(n, mid + 1, high);
		}
	}

	inline constexpr std::size_t sqrt(std::size_t n)
	{
		return sqrt_impl(n, 1, n);
	}
}
