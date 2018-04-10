#include "huffman.h"
#include <iostream>
#include <queue>
#include <vector>

Node::Node(char c, unsigned int occurences) : left_(nullptr), right_(nullptr), c_(c), occurences_(occurences) {
}

Node::Node(Node* left, Node* right, unsigned int occurences) : left_(left), right_(right), c_(0), occurences_(occurences) {
}

Node::Node(std::unique_ptr<Node> left, std::unique_ptr<Node> right, unsigned int occurences) : owned_left_(std::move(left)), owned_right_(std::move(right)), left_(owned_left_.get()), right_(owned_right_.get()), c_(0), occurences_(occurences) {
}

bool Node::isLeaf() const {
  return (left_ == nullptr && right_ == nullptr && c_ != '\0');
}

unsigned int Node::occurences() const {
  return occurences_;
}

char Node::character() const {
  return c_;
}

Node* Node::left() const {
  return left_;
}

namespace {
Node* getOrAllocate(Node** ptr, std::unique_ptr<Node>* owned) {
  if (*ptr == nullptr) {
    owned->reset(new Node(nullptr, nullptr));
    *ptr = owned->get();
  }
  return *ptr;
}
}

Node* Node::leftOrNew() {
  return getOrAllocate(&left_, &owned_left_);
}

Node* Node::rightOrNew() {
  return getOrAllocate(&right_, &owned_right_);
}


Node* Node::right() const {
  return right_;
}

void Node::addOccurence(unsigned int n) {
  occurences_ += n;
}

void Node::setLeft(Node *left) {
  left_ = left;
}

void Node::setRight(Node *right) {
  right_ = right;
}

void Node::setChar(char c) {
  c_ = c;
}

bool moreFrequent(const Node& lhs, const Node& rhs) {
  return lhs.occurences() > rhs.occurences();
}

void buildTable_(const Node& root, const std::string& path, std::vector<std::string>& result) {
  if (root.isLeaf()) {
    result[root.character()] = path;
  } else {
    if (root.left() != nullptr) {
      buildTable_(*root.left(), path + "0", result);
    }
    if (root.right() != nullptr) {
      buildTable_(*root.right(), path + "1", result);
    }
  }
}

std::vector<std::string> buildTable(const Node& root) {
  std::vector<std::string> result(256);
  buildTable_(root, "", result);
  return result;
}

std::unique_ptr<Node> trieFromTable(const std::vector<std::string>& table) {
  std::unique_ptr<Node> result(new Node(nullptr, nullptr));
  for(unsigned int c = 0; c < table.size(); ++c) {
    Node* current = result.get();
    for (auto d : table[c]) {
      if (d == '0') {
        current = current->leftOrNew();
      } else if (d == '1') {
        current = current->rightOrNew();
      }
      // TODO(cpitrat): Handle bad input
    }
    current->setChar(c);
  }
  return result;
}

std::vector<unsigned int> computeFrequencies(const std::string& content) {
  std::vector<unsigned int> result(256);
  for (auto c : content) {
    result[c] += 1;
  }
  return result;
}

std::unique_ptr<Node> buildTrie(const std::vector<unsigned int>& freqs) {
  auto f = [](const Node* lhs, const Node* rhs) -> bool { return moreFrequent(*lhs, *rhs); };
  std::priority_queue<Node*, std::vector<Node*>, decltype(f)> pq(f);
  for (unsigned int c = 0; c < freqs.size(); ++c) {
    if(freqs[c] > 0) {
      pq.push(new Node(c, freqs[c]));
    }
  }

  // Artificially add a node if the priority queue has only one element (single
  // letter content) as otherwise the trie consists of only the root node.
  if (pq.size() == 1) {
    pq.push(new Node(pq.top()->character(), 0));
  }
  while (pq.size() > 1) {
    Node* n1 = pq.top();
    pq.pop();
    Node* n2 = pq.top();
    pq.pop();
    pq.push(new Node(std::unique_ptr<Node>(n1), std::unique_ptr<Node>(n2), n1->occurences() + n2->occurences()));
  }
  std::unique_ptr<Node> result(pq.top());
  return result;
}

std::string encodeContent(const std::vector<std::string> table, const std::string& content) {
  std::string result;
  for (auto c : content) {
    result += table[c];
  }
  return result;
}

std::string encodeChar(char c) {
  std::string result(8, '\0');
  for(int i = 0; i < 8; ++i) {
    result[7-i] = '0' + ((c >> i) & 1);
  }
  return result;
}

std::string encodeTrie(const Node& trie) {
  std::string result;
  if (trie.isLeaf()) {
    return "1" + encodeChar(trie.character());
  }
  return "0" + encodeTrie(*trie.left()) + encodeTrie(*trie.right());
}

std::string decodeContent(const Node& trie, const std::string& content) {
  const Node *current = &trie;
  std::string result;
  for (auto c : content) {
    if (c == '0') {
      current = current->left();
    } else if (c == '1') {
      current = current->right();
    }
    if(current->isLeaf()) {
      result += current->character();
      current = &trie;
    }
  }
  return result;
}

char decodeChar(const std::string& decoded) {
  char result = 0;
  for(int i = 0; i < 8; ++i) {
    result = (result << 1) + (decoded[i] == '1' ? 1 : 0);
  }
  return result;
}

const char* decodeTrie(Node* node, const char* encoded) {
	if (*encoded == '0') {
		encoded = decodeTrie(node->leftOrNew(), &encoded[1]);
		encoded = decodeTrie(node->rightOrNew(), encoded);
	} else if (*encoded == '1') {
		node->setChar(decodeChar(std::string(&encoded[1], 8)));
		encoded = &encoded[9];
	}
	// TODO(cpitrat): Handle bad input
	return encoded;
}

std::unique_ptr<Node> decodeTrie(const std::string& encoded, const char** encoded_content) {
  std::unique_ptr<Node> result(new Node(nullptr, nullptr));
  *encoded_content = decodeTrie(result.get(), encoded.c_str());
  return result;
}

std::string compress(const std::string& content) {
  auto freqs = computeFrequencies(content);
  auto trie = buildTrie(freqs);
  auto table = buildTable(*trie);
  auto compressedContent = encodeContent(table, content);
	auto encodedTrie = encodeTrie(*trie);
  return encodedTrie + compressedContent;
}

std::string decompress(const std::string& decompress) {
  const char *encoded_content = nullptr;
  auto trie = decodeTrie(decompress, &encoded_content);
  return decodeContent(*trie, std::string(encoded_content));
}
