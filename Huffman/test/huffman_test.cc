#include "huffman.h"
#include <gtest/gtest.h>
#include <sstream>

TEST(NodeTest, isLeaf) {
  Node l1('a');
  Node l2('b');
  Node l3('c');
  Node i1(&l1, &l2);
  Node root(&i1, &l3);

  EXPECT_FALSE(root.isLeaf());
  EXPECT_FALSE(i1.isLeaf());
  EXPECT_TRUE(l1.isLeaf());
  EXPECT_TRUE(l2.isLeaf());
  EXPECT_TRUE(l3.isLeaf());
}

TEST(NodeTest, moreFrequent) {
  Node l1('b');
  Node l2('a');
  Node l3('c');
  Node i1(&l1, &l2);
  Node i2(&l1, &l3);
  Node i3(&l2, &l3);
  l1.addOccurence(1);
  l2.addOccurence(2);
  l3.addOccurence(3);
  i1.addOccurence(1);
  i2.addOccurence(2);
  i3.addOccurence(3);

  EXPECT_TRUE(moreFrequent(l2, l1));
  EXPECT_TRUE(moreFrequent(l3, l1));
  EXPECT_TRUE(moreFrequent(l3, l2));
  EXPECT_FALSE(moreFrequent(l1, l2));
  EXPECT_FALSE(moreFrequent(l1, l3));
  EXPECT_FALSE(moreFrequent(l2, l3));

  EXPECT_TRUE(moreFrequent(i2, l1));
  EXPECT_TRUE(moreFrequent(i3, l1));
  EXPECT_TRUE(moreFrequent(i3, l2));
  EXPECT_FALSE(moreFrequent(i1, l2));
  EXPECT_FALSE(moreFrequent(i1, l3));
  EXPECT_FALSE(moreFrequent(i2, l3));

  EXPECT_TRUE(moreFrequent(l2, i1));
  EXPECT_TRUE(moreFrequent(l3, i1));
  EXPECT_TRUE(moreFrequent(l3, i2));
  EXPECT_FALSE(moreFrequent(l1, i2));
  EXPECT_FALSE(moreFrequent(l1, i3));
  EXPECT_FALSE(moreFrequent(l2, i3));
}

TEST(NodeTest, buildTable) {
  Node l1('a');
  Node l2('b');
  Node l3('c');
  Node l4('d');
  Node l5('e');
  Node i1(&l1, &l2);
  Node i2(&i1, &l3);
  Node i3(&l4, &l5);
  Node root(&i2, &i3);

  auto table = buildTable(root);

  EXPECT_EQ(table['a'], "000");
  EXPECT_EQ(table['b'], "001");
  EXPECT_EQ(table['c'], "01");
  EXPECT_EQ(table['d'], "10");
  EXPECT_EQ(table['e'], "11");
}

TEST(NodeTest, trieFromTable) {
  std::vector<std::string> table(256);
  table['a'] = "000";
  table['b'] = "001";
  table['c'] = "01";
  table['d'] = "10";
  table['e'] = "11";

  auto root = trieFromTable(table);

  EXPECT_FALSE(root->isLeaf());
  ASSERT_TRUE(root->left() != nullptr);
  ASSERT_TRUE(root->left()->left() != nullptr);
  ASSERT_TRUE(root->left()->left()->left() != nullptr);
  ASSERT_TRUE(root->left()->left()->right() != nullptr);
  ASSERT_TRUE(root->left()->right() != nullptr);
  ASSERT_TRUE(root->right()->left() != nullptr);
  ASSERT_TRUE(root->right()->right() != nullptr);
  EXPECT_FALSE(root->left()->isLeaf());
  EXPECT_FALSE(root->left()->left()->isLeaf());
  EXPECT_FALSE(root->right()->isLeaf());

  auto a = root->left()->left()->left();
  auto b = root->left()->left()->right();
  auto c = root->left()->right();
  auto d = root->right()->left();
  auto e = root->right()->right();
  EXPECT_TRUE(a->isLeaf());
  EXPECT_TRUE(b->isLeaf());
  EXPECT_TRUE(c->isLeaf());
  EXPECT_TRUE(d->isLeaf());
  EXPECT_TRUE(e->isLeaf());
  EXPECT_EQ('a', a->character());
  EXPECT_EQ('b', b->character());
  EXPECT_EQ('c', c->character());
  EXPECT_EQ('d', d->character());
  EXPECT_EQ('e', e->character());
}

TEST(NodeTest, computeFrequencies) {
  std::string content = "Do not worry about your difficulties in Mathematics. I can assure you mine are still greater.";

  auto freqs = computeFrequencies(content);

  EXPECT_EQ(freqs['j'], 0u);
  EXPECT_EQ(freqs['k'], 0u);
  EXPECT_EQ(freqs['p'], 0u);
  EXPECT_EQ(freqs['q'], 0u);
  EXPECT_EQ(freqs['v'], 0u);
  EXPECT_EQ(freqs['x'], 0u);
  EXPECT_EQ(freqs['z'], 0u);
  EXPECT_EQ(freqs['D'], 1u);
  EXPECT_EQ(freqs['o'], 6u);
  EXPECT_EQ(freqs[' '], 15u);
  EXPECT_EQ(freqs['n'], 4u);
  EXPECT_EQ(freqs['t'], 7u);
  EXPECT_EQ(freqs['w'], 1u);
  EXPECT_EQ(freqs['r'], 7u);
  EXPECT_EQ(freqs['y'], 3u);
  EXPECT_EQ(freqs['a'], 7u);
  EXPECT_EQ(freqs['b'], 1u);
  EXPECT_EQ(freqs['u'], 5u);
  EXPECT_EQ(freqs['d'], 1u);
  EXPECT_EQ(freqs['i'], 7u);
  EXPECT_EQ(freqs['f'], 2u);
  EXPECT_EQ(freqs['c'], 3u);
  EXPECT_EQ(freqs['l'], 3u);
  EXPECT_EQ(freqs['e'], 7u);
  EXPECT_EQ(freqs['s'], 5u);
  EXPECT_EQ(freqs['h'], 1u);
  EXPECT_EQ(freqs['m'], 2u);
  EXPECT_EQ(freqs['.'], 2u);
  EXPECT_EQ(freqs['I'], 1u);
  EXPECT_EQ(freqs['g'], 1u);
}

TEST(NodeTest, buildTrie) {
  std::vector<unsigned int> freqs(256);
  freqs['a'] = 6;
  freqs['b'] = 2;
  freqs['c'] = 1;
  freqs['d'] = 4;
  freqs['e'] = 5;

  auto trie = buildTrie(freqs);
  auto table = buildTable(*trie);

  EXPECT_EQ("000", table['c']);
  EXPECT_EQ("001", table['b']);
  EXPECT_EQ("01", table['d']);
  EXPECT_EQ("10", table['e']);
  EXPECT_EQ("11", table['a']);
}

struct CompressionTestCase {
  std::string content;
  std::string encodedTrie;
  std::string encodedContent;
  std::vector<unsigned int> freqs;
};

TEST(NodeTest, encodeChar) {
  EXPECT_EQ("01000001", encodeChar('A'));
  EXPECT_EQ("01100001", encodeChar('a'));
  EXPECT_EQ("01100101", encodeChar('e'));
}

TEST(NodeTest, decodeChar) {
  EXPECT_EQ('A', decodeChar("01000001"));
  EXPECT_EQ('a', decodeChar("01100001"));
  EXPECT_EQ('e', decodeChar("01100101"));
}

TEST(NodeTest, decodeContent) {
  std::string content = "111111111111001001000010101011010101010";
  std::string expected = "aaaaaabbcddddeeeee";
  auto trie = buildTrie(computeFrequencies(expected));
  EXPECT_EQ("", decodeContent(*trie, ""));
  EXPECT_EQ("a", decodeContent(*trie, "11"));
  EXPECT_EQ("d", decodeContent(*trie, "01"));
  EXPECT_EQ("c", decodeContent(*trie, "000"));
  EXPECT_EQ(expected, decodeContent(*trie, content));
}

TEST(NodeTest, decodeContentSingleChar) {
  std::string content = "11111";
  std::string expected = "aaaaa";
  auto trie = buildTrie(computeFrequencies(expected));
  EXPECT_EQ(expected, decodeContent(*trie, content));
}

TEST(NodeTest, decodeTrie) {
  std::string encoded = "0001011000111011000101011001000101100101101100001";

  std::vector<std::string> code(256);
  code['a'] = "11";
  code['b'] = "001";
  code['c'] = "000";
  code['d'] = "01";
  code['e'] = "10";

  const char *unused = nullptr;
  auto trie = decodeTrie(encoded, &unused);
  EXPECT_EQ(code, buildTable(*trie));
}

class CompressionTest : public testing::Test {
 public:
  void SetUp() override {
    {
      CompressionTestCase case1;
      case1.content = "aaaaaabbcddddeeeee";
      case1.freqs.resize(256);
      case1.freqs['a'] = 6;
      case1.freqs['b'] = 2;
      case1.freqs['c'] = 1;
      case1.freqs['d'] = 4;
      case1.freqs['e'] = 5;
      // 0001<c>1<b>1<d>01<e>1<a>
      // a = 01100001 -> e = 01100101
      case1.encodedTrie = "0001011000111011000101011001000101100101101100001";
      case1.encodedContent = "111111111111001001000010101011010101010";
      cases.push_back(case1);
    }

    {
      CompressionTestCase case2;
      case2.content = "aaaaa";
      case2.freqs.resize(256);
      case2.freqs['a'] = 5;
      // 01<a>1<a>
      case2.encodedTrie = "0101100001101100001";
      case2.encodedContent = "11111";
      cases.push_back(case2);
    }
  }

 protected:
  std::vector<CompressionTestCase> cases;
};

TEST_F(CompressionTest, encodeTrie) {
  for (const auto& testCase : cases) {
    auto trie = buildTrie(testCase.freqs);
    EXPECT_EQ(testCase.encodedTrie, encodeTrie(*trie));
  }
}

TEST_F(CompressionTest, encodeContent) {
  for (const auto& testCase : cases) {
    std::string content = testCase.content;
    auto trie = buildTrie(computeFrequencies(content));
    auto table = buildTable(*trie);
    EXPECT_EQ(testCase.encodedContent, encodeContent(table, content));
  }
}

TEST_F(CompressionTest, compress) {
  for (const auto& testCase : cases) {
    std::string compressed = testCase.encodedTrie + testCase.encodedContent;
    EXPECT_EQ(compressed, compress(testCase.content));
  }
}

TEST_F(CompressionTest, decompress) {
  for (const auto& testCase : cases) {
    std::string compressed = testCase.encodedTrie + testCase.encodedContent;
    EXPECT_EQ(testCase.content, decompress(compressed));
  }
}
