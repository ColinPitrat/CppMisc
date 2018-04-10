#pragma once
#include <vector>
#include <string>
#include <memory>

// Node represents a node of the Huffman Trie.
class Node {
 public:
  explicit Node(char c, unsigned int occurences = 0);
  Node(Node* left, Node* right, unsigned int occurences = 0);
  Node(std::unique_ptr<Node> left, std::unique_ptr<Node> right, unsigned int occurences = 0);

  bool isLeaf() const;
  unsigned int occurences() const;
  char character() const;
  Node* left() const;
  Node* right() const;
  Node* leftOrNew();
  Node* rightOrNew();

  void addOccurence(unsigned int n);
  void setLeft(Node *left);
  void setRight(Node *right);
  void setChar(char c);

 private:
  std::unique_ptr<Node> owned_left_, owned_right_;
  Node *left_, *right_;
  char c_;
  unsigned int occurences_;
};

bool moreFrequent(const Node& lhs, const Node& rhs);

void buildTable_(const Node& root, const std::string& path, std::vector<std::string>& result);

std::vector<std::string> buildTable(const Node& root);

std::unique_ptr<Node> trieFromTable(const std::vector<std::string>& table);

std::vector<unsigned int> computeFrequencies(const std::string& content);

std::unique_ptr<Node> buildTrie(const std::vector<unsigned int>& freqs);

std::string encodeContent(const std::vector<std::string> table, const std::string& content);
std::string encodeChar(char c);
std::string encodeTrie(const Node& trie);

std::string decodeContent(const Node& trie, const std::string& content);
char decodeChar(const std::string& decoded);
std::unique_ptr<Node> decodeTrie(const std::string& encoded);

std::string compress(const std::string& content);
