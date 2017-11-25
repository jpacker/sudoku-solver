#include <array>
#include <algorithm>
#include <iostream>
#include <optional>

#include "meta.hpp"

namespace solver {
	template <std::size_t N>
	using Puzzle = std::array<std::array<unsigned, N>, N>;

	template <std::size_t N>
	inline bool IsNumberInRow(const Puzzle<N>& p, unsigned number, unsigned row);
	template <std::size_t N>
	inline bool IsNumberInCol(const Puzzle<N>& p, unsigned number, unsigned col);
	template <std::size_t N>
	inline bool IsNumberInBlock(const Puzzle<N>& p, unsigned number, unsigned block);
	template <std::size_t N>
	inline std::array<unsigned, N> Candidates
		(
			const Puzzle<N>& p, 
			unsigned row, 
			unsigned col
		);
	template <std::size_t N>
	inline std::optional<Puzzle<N>> SolveBacktrack(const Puzzle<N>& p);
	template <std::size_t N>
	inline Puzzle<N> Solve(const Puzzle<N>& p);

	template <std::size_t N>
	std::ostream& operator<<(std::ostream& os, const Puzzle<N>& p)
	{
		for(const auto r : p)
		{
			for(const auto c : r)
			{
				os << c << " ";
			}
			os << '\n';
		}
		return os;
	}

	template <std::size_t N>
	inline std::optional<Puzzle<N>> SolveBacktrack(const Puzzle<N>& p)
	{
		std::size_t row = 0, col = 0;
		auto found = false;
		for(; row < N; ++row)
		{
			for(col = 0; col < N && !found; ++col)
			{
				if(p[row][col] == 0)
				{
					found = true;
					break;
				}
			}
			if(found)
				break;
		}


		// Solved the puzzle
		if(!found)
			return std::optional{p};

		const auto candidates = Candidates(p, row, col);
		for(const auto c : candidates)
		{
			if(c == 0)
				break;

			auto p2 = p;
			p2[row][col] = c;
			auto solved = SolveBacktrack(p2);
			if(solved.has_value())
				return solved;
		}
		return std::optional<Puzzle<N>>{};
	}

	template <std::size_t N>
	inline std::array<unsigned, N> Candidates
		(
			const Puzzle<N>& p, 
			unsigned row, 
			unsigned col
		) 
	{
		std::array<unsigned, N> c{};
		const auto blockSize = meta::sqrt(N);
		const auto block = (row / blockSize) * blockSize + (col / blockSize);
		std::size_t j = 0;
		for(std::size_t i = 1; i <= N; ++i)
		{
			if(!IsNumberInRow<N>(p, i, row) && !IsNumberInCol<N>(p, i, col)
					&& !IsNumberInBlock<N>(p, i, block) )
			{
				c[j] = i;
				++j;
			}
		}
		return c;
	}

	template <std::size_t N>
	inline bool IsNumberInRow(const Puzzle<N>& p, unsigned number, unsigned row) 
	{
		auto found = false;
		for(std::size_t col = 0; col < N && !found; ++col)
		{
			found = found || p[row][col] == number;
		}
		return found;
	}
	
	template <std::size_t N>
	inline bool IsNumberInCol(const Puzzle<N>& p, unsigned number, unsigned col) 
	{
		auto found = false;
		for(std::size_t i = 0; i < N && !found; ++i)
		{
			found = found || p[i][col] == number;
		}
		return found;
	}

	template <std::size_t N>
	inline bool IsNumberInBlock(const Puzzle<N>&p, unsigned number, unsigned block)
	{
		// blocks are numbers top->bottom, left->right from 0 to N.
		constexpr auto blockSize = meta::sqrt(N);
		const auto blockRow = static_cast<std::size_t>(block / blockSize) * blockSize;
		const auto blockCol = static_cast<std::size_t>(block % blockSize) * blockSize;
		for(std::size_t i = 0; i < blockSize; ++i)
		{
			const auto row = i + blockRow;
			for(std::size_t j = 0; j < blockSize; ++j)
			{
				const auto col = j + blockCol;
				if(p[row][col] == number)
				{
					return true;
				}
			}
		}
		return false;
	}
}
