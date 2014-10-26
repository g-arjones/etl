
#include <UnitTest++/UnitTest++.h>

#include "../Array.h"

#include <array>
#include <vector>
#include <algorithm>

namespace 
{		
  SUITE(ArrayTest)
  {
    static const size_t SIZE = 10;

    typedef etl::array<int, SIZE> Data;
    typedef std::vector<int>      TestData;

    Data data;
    TestData testData;
    TestData initialData;

    //*************************************************************************
    struct SetupFixture
    {
      SetupFixture()
      {
        int n[] = { 2, 1, 4, 3, 6, 5, 8, 7, 10, 9 };

        std::copy(std::begin(n), std::end(n), data.begin());
        initialData.assign(std::begin(n), std::end(n));
        testData.assign(std::begin(n), std::end(n));
      }
    };
    
    //*************************************************************************
    TEST(DefaultConstructor)
    {
      Data data;

      CHECK_EQUAL(data.size(), size_t(SIZE));
      CHECK_EQUAL(data.max_size(), SIZE);
    }

    //*************************************************************************
    TEST_FIXTURE(SetupFixture, Iterator)
    {
      bool isEqual = std::equal(data.begin(),
                                data.end(),
                                testData.begin());

      CHECK(isEqual);
    }

    //*************************************************************************
    TEST_FIXTURE(SetupFixture, ConstIterator)
    {
      bool isEqual = std::equal(data.cbegin(),
                                data.cend(),
                                testData.cbegin());

      CHECK(isEqual);
    }

    //*************************************************************************
    TEST_FIXTURE(SetupFixture, ReverseIterator)
    {
      bool isEqual = std::equal(data.rbegin(),
                                data.rend(),
                                testData.rbegin());

      CHECK(isEqual);
    }

    //*************************************************************************
    TEST_FIXTURE(SetupFixture, ConstReverseIterator)
    {
      bool isEqual = std::equal(data.crbegin(),
                                data.crend(),
                                testData.crbegin());

      CHECK(isEqual);
    }

    //*************************************************************************
    TEST(Begin)
    {
      Data data = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
      const Data constData = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

      CHECK_EQUAL(data.begin(), &data[0]);
      CHECK_EQUAL(constData.cbegin(), &constData[0]);
    }

    //*************************************************************************
    TEST(End)
    {
      Data data = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
      const Data constData = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

      CHECK_EQUAL(data.end(), &data[SIZE]);
      CHECK_EQUAL(constData.cend(), &constData[SIZE]);
    }

    //*************************************************************************
    TEST_FIXTURE(SetupFixture, Indexing)
    {
      for (size_t i = 0; i < data.size(); ++i)
      {
        CHECK_EQUAL(data[i], testData[i]);
      }
    }

    //*************************************************************************
    TEST_FIXTURE(SetupFixture, IndexingConst)
    {
      for (size_t i = 0; i < data.size(); ++i)
      {
        CHECK_EQUAL(data[i], testData[i]);
      }
    }

    //*************************************************************************
    TEST_FIXTURE(SetupFixture, at)
    {
      for (size_t i = 0; i < data.size(); ++i)
      {
        CHECK_EQUAL(data.at(i), testData.at(i));
      }

      bool gotException = false;

      try
      {
        data.at(data.size());
      }
      catch (etl::array_out_of_range_exception)
      {
        gotException = true;
      }

      CHECK(gotException);
    }

    //*************************************************************************
    TEST_FIXTURE(SetupFixture, AtConst)
    {
      for (size_t i = 0; i < data.size(); ++i)
      {
        CHECK_EQUAL(data.at(i), testData.at(i));
      }

      bool gotException = false;

      try
      {
        data.at(data.size());
      }
      catch (etl::array_out_of_range_exception)
      {
        gotException = true;
      }

      CHECK(gotException);
    }

    //*************************************************************************
    TEST_FIXTURE(SetupFixture, Front)
    {
      CHECK(data.front() == testData.front());
    }

    //*************************************************************************
    TEST_FIXTURE(SetupFixture, Back)
    {
      CHECK(data.back() == testData.back());
    }

    //*************************************************************************
    TEST_FIXTURE(SetupFixture, Assignment)
    {
      Data otherData;

      otherData = data;

      bool isEqual = std::equal(data.begin(),
                                data.end(),
                                otherData.begin());

      CHECK(isEqual);
    }

    //*************************************************************************
    TEST(Fill)
    {
      Data data;
      data.fill(1);

      TestData testData(data.max_size(), 1);

      bool isEqual = std::equal(data.begin(),
                                data.end(),
                                testData.begin());

      CHECK(isEqual);
    }

    //*************************************************************************
    TEST_FIXTURE(SetupFixture, DataAccess)
    {
      bool isEqual = std::equal(data.begin(),
                                data.end(),
                                data.data());

      CHECK(isEqual);
    }

    //*************************************************************************
    TEST_FIXTURE(SetupFixture, Swap)
    {
      TestData testData2(initialData.begin() + 2, initialData.end());
      Data otherData;
      std::copy(initialData.begin() + 2, initialData.end(), otherData.begin());

      testData.swap(testData2);

      data.swap(otherData);

      bool isEqual = std::equal(testData.begin(),
                                testData.end(),
                                data.begin());

      CHECK(isEqual);
    }

    //*************************************************************************
    TEST(Equal)
    {
      const Data data1 = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
      const Data data2 = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
      CHECK(data1 == data2);

      const Data data = { 1, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
      CHECK(data1 != data);
    }

    //*************************************************************************
    TEST(NotEqual)
    {
      const Data data1 = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
      const Data data2 = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
      CHECK(data1 == data2);

      const Data data3 = { 1, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
      CHECK(data1 != data3);
    }

    //*************************************************************************
    TEST(GreaterThan)
    {
      const Data lesser = { 0, 1, 2, 3, 4, 4, 6, 7, 8, 9 };
      const Data data = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
      CHECK(lesser <= data);

      const Data greater = { 0, 1, 2, 3, 5, 5, 6, 7, 8, 9 };
      CHECK(greater > data);
    }

    //*************************************************************************
    TEST(LessThan)
    {
      const Data lesser  = { 0, 1, 2, 3, 4, 4, 6, 7, 8, 9 };
      const Data data = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
      CHECK(lesser < data);

      const Data greater = { 0, 1, 2, 3, 5, 5, 6, 7, 8, 9 };
      CHECK(greater >= data);
    }

    //*************************************************************************
    TEST(GreaterThanEqual)
    {
      const Data lesser = { 0, 1, 2, 3, 4, 4, 6, 7, 8, 9 };
      const Data data = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
      CHECK(lesser < data);

      const Data greater = { 0, 1, 2, 3, 5, 5, 6, 7, 8, 9 };
      CHECK(greater >= data);

      const Data data2 = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
      CHECK(data2 >= data);
    }

    //*************************************************************************
    TEST(LessThanEqual)
    {
      const Data lesser  = { 0, 1, 2, 3, 4, 4, 6, 7, 8, 9 };
      const Data data = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
      CHECK(lesser <= data);

      const Data greater = { 0, 1, 2, 3, 5, 5, 6, 7, 8, 9 };
      CHECK(greater > data);

      const Data data2 = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
      CHECK(data2 <= data);
    }
  };
}