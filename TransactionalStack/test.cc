#include <list>
#include <iostream>

using namespace std;

enum Action {
	PUSH,
	POP
};

class Operation {
	public:
		Operation(Action a, int v) : action_(a), value_(v) {}

		Action action_;
		int value_;
};

class Transaction {
	public:
		ostream& toStream(ostream& os) {
			for(const auto &op : rollback_operations_) {
				switch(op.action_) {
					case PUSH:
						os << "  PUSH " << op.value_;
						break;
					case POP:
						os << "  POP ";
						break;
					default:
						os << "  ** ERROR ** ";
				}
				os << endl;
			}
		}

		list<Operation> rollback_operations_;
};

class Solution {
	public:
		Solution() {
		}

		void push(int value) {
			content_.push_back(value);
			if(!transactions_.empty()) {
				transactions_.back().rollback_operations_.push_front(Operation(POP, 0));
			}
		}

		int top() {
			if (content_.empty()) return 0;
			return content_.back();
		}

		void pop() {
			if (!content_.empty()) {
				int value = top();
				content_.pop_back();
				if(!transactions_.empty()) {
					transactions_.back().rollback_operations_.push_front(Operation(PUSH, value));
				}
			}
		}

		void begin() {
			transactions_.emplace_back();
		}

		bool rollback() {
			if (transactions_.empty()) {
        return false;
      }
      for(const auto& op : transactions_.back().rollback_operations_) {
        switch(op.action_) {
          case PUSH:
            content_.push_back(op.value_);
            break;
          case POP:
            content_.pop_back();
            break;
          default:
            throw "Unexpected operation type in rollback logs";
        }
      }
      transactions_.pop_back();
      return true;
		}

		bool commit() {
			if (transactions_.empty()) {
        return false;
      }
      if (transactions_.size() > 1) {
        // Merge last transaction with the previous
        auto current_transaction = transactions_.rbegin();
        auto previous_transaction = current_transaction;
        ++previous_transaction;
        auto curr_trx_ops = &current_transaction->rollback_operations_;
        auto prev_trx_ops = &previous_transaction->rollback_operations_;
        prev_trx_ops->splice(prev_trx_ops->begin(), *curr_trx_ops);
      }
      transactions_.pop_back();
      return true;
		}

	private:
		list<int> content_;
		list<Transaction> transactions_;
};

// Here begins the tests part ...

#define ASSERT_EQUAL(x,y) assert_equal(x, y, __FILE__, __LINE__);

static int nb_tests = 0;

void assert_equal(int x, int y, string file, int line)
{
	if (x != y)
	{
    cout << "ERROR: " << file << ":" << line << " " << x << " != " << y << endl;
    throw "Failed test";
	}
  nb_tests++;
}

void test_top_on_empty_stack() {
	Solution sol;
	ASSERT_EQUAL(sol.top(), 0);
}

void test_pop_on_empty_stack() {
	Solution sol;
	sol.pop();
}

void test_simple_push_top() {
	Solution sol;
	sol.push(42);
	ASSERT_EQUAL(sol.top(), 42);
	ASSERT_EQUAL(sol.top(), 42);
}

void test_multiple_push_top_pop() {
	Solution sol;
	sol.push(1);
	sol.push(2);
	sol.push(3);
	sol.push(4);
	sol.push(5);
	ASSERT_EQUAL(sol.top(), 5);
	sol.pop();
	ASSERT_EQUAL(sol.top(), 4);
	sol.pop();
	ASSERT_EQUAL(sol.top(), 3);
	sol.pop();
	ASSERT_EQUAL(sol.top(), 2);
	sol.pop();
	ASSERT_EQUAL(sol.top(), 1);
	sol.pop();
	ASSERT_EQUAL(sol.top(), 0);
	sol.pop();
	ASSERT_EQUAL(sol.top(), 0);
	sol.push(6);
	ASSERT_EQUAL(sol.top(), 6);
}

void test_commit_without_transaction() {
	Solution sol;
	ASSERT_EQUAL(sol.commit(), false);
}

void test_rollback_without_transaction() {
	Solution sol;
	sol.rollback();
}

void test_simple_transaction_rollback() {
	Solution sol;
	sol.push(1);
	sol.push(2);
	sol.begin();
	sol.push(3);
	sol.push(4);
	sol.rollback();
	ASSERT_EQUAL(sol.top(), 2);
}

void test_simple_transaction_commit() {
	Solution sol;
	sol.push(1);
	sol.push(2);
	sol.begin();
	sol.push(3);
	sol.push(4);
	sol.commit();
	ASSERT_EQUAL(sol.top(), 4);
}

void test_nested_transactions() {
	Solution sol;
	sol.push(1);
	sol.push(2);
	sol.begin();
	sol.push(3);
	sol.push(4);
	sol.begin();
	sol.push(5);
	sol.push(6);
	sol.begin();
	sol.push(7);
	sol.push(8);
	sol.begin();
	sol.push(9);
	sol.push(10);
	ASSERT_EQUAL(sol.top(), 10);
	sol.pop();
	ASSERT_EQUAL(sol.top(), 9);
	sol.rollback();
	ASSERT_EQUAL(sol.top(), 8);
	sol.pop();
	ASSERT_EQUAL(sol.top(), 7);
	sol.commit();
	ASSERT_EQUAL(sol.top(), 7);
	sol.pop();
	ASSERT_EQUAL(sol.top(), 6);
	sol.rollback();
	ASSERT_EQUAL(sol.top(), 4);
	sol.pop();
	ASSERT_EQUAL(sol.top(), 3);
	sol.pop();
	ASSERT_EQUAL(sol.top(), 2);
	sol.pop();
	ASSERT_EQUAL(sol.top(), 1);
	sol.pop();
	ASSERT_EQUAL(sol.top(), 0);
	sol.pop();
	ASSERT_EQUAL(sol.top(), 0);
	sol.rollback();
	ASSERT_EQUAL(sol.top(), 2);
	sol.rollback();
	ASSERT_EQUAL(sol.top(), 2);
	sol.commit();
	ASSERT_EQUAL(sol.top(), 2);
	sol.pop();
	ASSERT_EQUAL(sol.top(), 1);
	sol.pop();
	ASSERT_EQUAL(sol.top(), 0);
	sol.pop();
	ASSERT_EQUAL(sol.top(), 0);
	sol.rollback();
	ASSERT_EQUAL(sol.top(), 0);
	sol.rollback();
	ASSERT_EQUAL(sol.top(), 0);
}

int main() {
	test_top_on_empty_stack();
	test_pop_on_empty_stack();
	test_simple_push_top();
	test_multiple_push_top_pop();
	test_commit_without_transaction();
	test_rollback_without_transaction();
	test_simple_transaction_rollback();
	test_simple_transaction_commit();
	test_nested_transactions();
  cout << nb_tests << " tests OK" << endl;
	return 0;
}
