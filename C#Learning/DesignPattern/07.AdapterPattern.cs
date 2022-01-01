// 适配器模式
namespace AdapterSample
{
    interface ScoreOperation
    {
        int[] Sort( int[] array );           // 成绩排序
        int Search( int[] array, int key );  // 成绩查找
    }

    // 快速排序类
    class QuickSortClass
    {
        public int[] QuickSort( int[] array )
        {
            Sort(array, 0, array.Length - 1);
            return array;
        }

        public void Sort( int[] array, int p, int r )
        {
            int q = 0;
            if( p < r )
            {
                q = Partition(array, p, r);
                Sort(array, p, q - 1);
                Sort(array, q + 1, r);
            }
        }

        public int Partition( int[] a, int p, int r )
        {
            int x = a[r];
            int j = p - 1;
            for( int i = p; i <= r - 1; i++ )
            {
                if( a[i] <= x )
                {
                    j++;
                    Swap(a, j, i);
                }
            }
            Swap(a, j + 1, r);
            return j + 1;
        }

        public void Swap( int[] a, int i, int j )
        {
            int t = a[i];
            a[i] = a[j];
            a[j] = t;
        }
    }

    // 二分查找类
    class BinarySearchClass
    {
        public int BinarySearch( int[] array, int key )
        {
            int low = 0;
            int high = array.Length - 1;
            while( low <= high )
            {
                int mid = (low + high) / 2;
                int midVal = array[mid];
                if( midVal < key )
                {
                    low = mid + 1;
                }
                else if( midVal > key )
                {
                    high = mid - 1;
                }
                else
                {
                    return 1;  // 找到元素返回1
                }
            }
            return -1;  // 未找到元素返回-1
        }
    }

    // 操作适配器
    class OperationAdapter : ScoreOperation
    {
        private QuickSortClass sortObj;
        private BinarySearchClass searchObj;

        public OperationAdapter()
        {
            sortObj = new QuickSortClass();
            searchObj = new BinarySearchClass();
        }

        public int[] Sort( int[] array )
        {
            return sortObj.QuickSort(array);
        }

        public int Search( int[] array, int key )
        {
            return searchObj.BinarySearch(array, key);
        }
    }
}
