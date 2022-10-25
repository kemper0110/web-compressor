#include "HuffmanTree.h"


namespace Huffman
{

	std::pair<
		std::vector<SignFrequency>,
		std::array<std::vector<bool>, MAX_SIGN_VALUE>
	>
		makeCompressorTree(std::istream& istream) {
		std::array<uint32_t, MAX_SIGN_VALUE> frequency_map{};

		std::for_each(std::istreambuf_iterator<char>{istream}, {}, [&frequency_map](char c) {
			const auto sign = static_cast<Sign>(c);
			frequency_map[sign]++;
			}
		);

		std::vector<SignFrequency> frequency_vec;
		frequency_vec.reserve(frequency_map.size());
		for (auto i = 0UL; i < frequency_map.size(); ++i)
			if (frequency_map[i])
				frequency_vec.push_back({static_cast<Sign>(i), frequency_map[i]});
//				frequency_vec.emplace_back(i, frequency_map[i]);

		std::sort(frequency_vec.begin(), frequency_vec.end(), [](const SignFrequency& lhs, const SignFrequency& rhs) {
			if (lhs.freq < rhs.freq)
				return true;
			if (lhs.freq > rhs.freq)
				return false;
			if (lhs.sign < rhs.sign)
				return true;
			return false;
			});

		//for (const auto& sf : frequency_vec) {
		//	std::cout << sf.sign << ": " << sf.freq << '\n';
		//}
		const auto [leafs, inner_nodes, root] = huffmanImpl(frequency_vec);


		std::array<std::vector<bool>, MAX_SIGN_VALUE> codemap;
		auto recursive_mapping = [&codemap](const CompressorNode* root, auto&& continuation, std::vector<bool>& vec) {
			if (root == nullptr) return;
			if (root->children[0] and root->children[1]) {
				vec.push_back(0);
				continuation(root->children[0], continuation, vec);
				vec.back() = 1;
				continuation(root->children[1], continuation, vec);
				vec.pop_back();
			}
			else {
				codemap[root->sign] = vec;
			}
		};
		std::vector<bool> v;
		v.reserve(256);
		recursive_mapping(root, recursive_mapping, v);

		std::cout << "\ncodemap\n";
		for (int i = 0; i < codemap.size(); ++i) {
			const auto& code = codemap[i];
			if (code.size() == 0) continue;
			std::cout << i << ": ";
			for (const auto bit : code)
				std::cout << bit;
			std::cout << '\n';
		}

		//auto sum = 0ULL;
		//for (const auto& sf : frequency_vec) {
		//	std::cout << (char)sf.sign << " : " << sf.freq << " : " << codemap[sf.sign].size() << '\n';
		//	sum += sf.freq * codemap[sf.sign].size();
		//}
		//std::cout << "sum = " << sum << '\n';


		return std::pair{ frequency_vec, codemap };
	}


	////std::vector<Sign>
	//std::tuple<std::vector<DecompressorNode>, std::vector<DecompressorNode>, DecompressorNode*>
	//	makeDecompressorTree(std::vector<SignFrequency>& frequency_vec) {

	//	//for (const auto& sf : frequency_vec) {
	//	//	std::cout << sf.sign << ": " << sf.freq << '\n';
	//	//}

	//	// frequency_vec must be already sorted
	//	auto [leafs, inner_nodes, root] = huffmanImpl(frequency_vec);
	//	

	//	//std::vector<DecompressorNode> leafs(frequency_vec.begin(), frequency_vec.end());
	//	//std::vector<DecompressorNode> inner_nodes(frequency_vec.size());

	//	//DecompressorNode* root = nullptr;

	//	//const auto getNext = [](std::vector<DecompressorNode>& vec, uint32_t i)
	//	//	//-> std::pair<CompressorNode&, CompressorNode&>
	//	//	-> std::pair<size_t, size_t>
	//	//{
	//	//	switch (vec.size() - i) {
	//	//	case 0:
	//	//		return { vec.size(), vec.size() };
	//	//	case 1:
	//	//		return { i, vec.size() };
	//	//	default:
	//	//		return { 
	//	//			i,
	//	//			vec[i].code_width == vec[i + 1].code_width ? i + 1 : vec.size()
	//	//		};
	//	//	}
	//	//};

	//	//uint32_t i = 0, j = 0;
	//	//for (auto k = 0UL; k < inner_nodes.size() - 1; ++k) {
	//	//	//inner_nodes[k] = CompressorNode{ 0, s1, &leaf1, &leaf2 };

	//	//	const auto [leaf_idx1, leaf_idx2] = getNext(leafs, i);
	//	//	if (leaf_idx2 != leafs.size()) {
	//	//		inner_nodes[k] = DecompressorNode{ 
	//	//			0, static_cast<unsigned char>(leafs[leaf_idx1].code_width - 1), &leafs[leaf_idx1], &leafs[leaf_idx2]
	//	//		};
	//	//		i += 2;
	//	//	}
	//	//	else {
	//	//		const auto [inner_idx1, inner_idx2] = getNext(inner_nodes, j);
	//	//		if (inner_idx2 != inner_nodes.size()) {
	//	//			inner_nodes[k] = DecompressorNode{
	//	//				0, static_cast<unsigned char>(inner_nodes[inner_idx1].code_width - 1), &inner_nodes[inner_idx1], &inner_nodes[inner_idx2]
	//	//			};
	//	//			j += 2;
	//	//		}
	//	//		else if (leaf_idx1 != leafs.size() and 
	//	//			inner_idx1 != inner_nodes.size()) {
	//	//			if (leafs[leaf_idx1].code_width == inner_nodes[inner_idx1].code_width) {
	//	//				inner_nodes[k] = DecompressorNode{
	//	//					0, static_cast<unsigned char>(leafs[leaf_idx1].code_width - 1), &leafs[leaf_idx1], &inner_nodes[inner_idx1]
	//	//				};
	//	//				i++;
	//	//				j++;
	//	//			}
	//	//			else {

	//	//			}
	//	//		}
	//	//		else {
	//	//			throw std::runtime_error("Huffman error: brother nodes were not found");
	//	//		}
	//	//	}
	//	//	root = &inner_nodes[k];
	//	//}

	//	


	//	
	//	std::array<std::vector<bool>, MAX_SIGN_VALUE> codemap;
	//	auto recursive_mapping = [&codemap](const DecompressorNode* root, auto&& continuation, std::vector<bool>& vec) {
	//		if (root == nullptr) return;
	//		if (root->children[0] and root->children[1]) {
	//			vec.push_back(0);
	//			continuation(root->children[0], continuation, vec);
	//			vec.back() = 1;
	//			continuation(root->children[1], continuation, vec);
	//			vec.pop_back();
	//		}
	//		else {
	//			codemap[root->sign] = vec;
	//		}
	//	};
	//	std::vector<bool> v;
	//	v.reserve(256);
	//	recursive_mapping(root, recursive_mapping, v);

	//	std::cout << "\ncodemap\n";
	//	for(int i = 0; i < codemap.size(); ++i){
	//		const auto& code = codemap[i];
	//		if (code.size() == 0) continue;
	//		std::cout << i << ": ";
	//		for (const auto bit : code)
	//			std::cout << bit;
	//		std::cout << '\n';
	//	}

	//	// requires at least 2 childrens of root
	//	assert(root != nullptr && root->children[0] != nullptr && root->children[1] != nullptr);
	//	for (auto& leaf : leafs) {
	//		leaf.children[0] = root->children[0];
	//		leaf.children[1] = root->children[1];
	//	}

	//	//std::vector<Sign> tree;
	//	//auto recursive_flatting = [&tree](const Node* root, auto&& continuation, const uint32_t idx = 0UL) {
	//	//	if (root == nullptr) return;
	//	//	if (root->children[0] and root->children[1]) {
	//	//		continuation(root->children[0], continuation, 2 * idx + 1);
	//	//		continuation(root->children[1], continuation, 2 * idx + 2);
	//	//	}
	//	//	else {
	//	//		if (idx >= tree.size()) {
	//	//			//const auto newsize = std::bit_ceil(idx);
	//	//			tree.resize(idx);
	//	//		}
	//	//		tree[idx] = root->sign;
	//	//	}
	//	//};
	//	//recursive_flatting(root, recursive_flatting);

	//	//return tree;
	//	return { std::move(leafs), std::move(inner_nodes), std::move(root) };
	//}



	std::tuple<std::vector<CompressorNode>, std::vector<CompressorNode>, CompressorNode*>
		huffmanImpl(std::vector<SignFrequency>& frequency_vec) {

        // frequency_vec.begin(), frequency_vec.end()
		auto leafs = std::vector<CompressorNode>();
        for(const auto& sf : frequency_vec)
            leafs.push_back(CompressorNode{sf});

		auto inner_nodes = std::vector<CompressorNode>(
			frequency_vec.size(),
			CompressorNode{ 0, std::numeric_limits<uint32_t>::max() / 2 }
		);


		const auto getMin = [](std::vector<CompressorNode>& nodelist, uint32_t i) -> std::pair<CompressorNode&, CompressorNode&> {
			static auto null = CompressorNode{ 0, std::numeric_limits<uint32_t>::max() / 2 };
			switch (nodelist.size() - i) {
			case 0:
				return { null, null };
			case 1:
				return { nodelist[i], null };
			default:
				return { nodelist[i], nodelist[size_t(i) + 1] };
			}
		};


		CompressorNode* root = nullptr;
		uint32_t i = 0, j = 0;
		for (auto k = 0UL; k < inner_nodes.size() - 1; ++k) {
			const auto [leaf1, leaf2] = getMin(leafs, i);
			const auto [node1, node2] = getMin(inner_nodes, j);
			const auto
				s1 = leaf1.freq + leaf2.freq,
				s2 = node1.freq + node2.freq,
				s3 = leaf1.freq + node1.freq;
			if (s1 <= s2 && s1 <= s3) {
				inner_nodes[k] = CompressorNode{ 0, s1, &leaf1, &leaf2 };
				i += 2;
			}
			else if (s2 <= s1 && s2 <= s3) {
				inner_nodes[k] = CompressorNode{ 0, s2, &node1, &node2 };
				j += 2;
			}
			else if (s3 <= s1 && s3 <= s2) {
				inner_nodes[k] = CompressorNode{ 0, s3, &leaf1, &node1 };
				i++; j++;
			}
			else
                std::exit(1);
//				throw std::runtime_error("Huffman error: least sum was not found");
			root = &inner_nodes[k];
		}


		return std::make_tuple(std::move(leafs), std::move(inner_nodes), root);
	}
}
