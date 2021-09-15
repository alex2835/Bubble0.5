#pragma once

#include <vector>
#include "ref.h"

namespace Bubble
{
	template <typename T>
	struct Tree
	{
		struct Node
		{
			Node() = default;
			Node(T data) 
				: mData(std::move(data))
			{}
			template <typename ...Args>
			Node(Args&& ...args)
				: mData(std::forward<Args>(args)...)
			{}

			Node(const Node&) = default;
			Node& operator=(const Node&) = default;
			Node(Node&&) = default;
			Node& operator=(Node&&) = default;

			T& GetData() { return mData; }
			void GetData(T elem) { mData = std::move(elem); }
			void Append(const Node& elem) { mChildren.push_back(elem); }
			void Append(Node&& elem) { mChildren.push_back(std::move(elem)); }
			template <typename ...Args>
			void Append(Args&& ...args) { mChildren.emplace_back(std::forward<Args>(args)...); }

			auto begin() { return mChildren.begin(); }
			auto end() { return mChildren.end(); }

			operator T&() { return mData; }

		private:
			T mData;
			std::vector<Node> mChildren;
		};

		Node& GetRoot() { return mRoot; }
		void SetRoot(Node node) { mRoot = std::move(node); }

	private:
		Node mRoot;
	};
}