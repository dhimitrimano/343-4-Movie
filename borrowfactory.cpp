#include "transaction.h"

BorrowFactory::BorrowFactory() { Transaction::rememberType('B', this); }

Transaction *BorrowFactory::create() const { return new Borrow(); }