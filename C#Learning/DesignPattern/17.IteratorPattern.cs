using System.Collections.Generic;

// 迭代器模式
namespace IteratorSample
{
    abstract class AbstractObjectList
    {
        protected List<object> objects = new List<object>();

        public AbstractObjectList( List<object> objects )
        {
            this.objects = objects;
        }

        public void AddObject( object obj )
        {
            this.objects.Add(obj);
        }

        public void RemoveObject( object obj )
        {
            this.objects.Remove(obj);
        }

        public List<object> GetObjects()
        {
            return this.objects;
        }

        public abstract AbstractIterator CreateIterator();
    }

    class ProductList : AbstractObjectList
    {
        public ProductList( List<object> products ) : base(products) { }

        public override AbstractIterator CreateIterator()
        {
            return new ProductIterator(this);
        }
    }


    interface AbstractIterator
    {
        void Next();
        bool IsLast();
        void Previous();
        bool IsFirst();
        object GetNextItem();
        object GetPreviousItem();
    }

    class ProductIterator : AbstractIterator
    {
        private ProductList productList;
        private List<object> products;
        private int cursor1, cursor2;

        public ProductIterator( ProductList list )
        {
            this.productList = list;
            this.products = list.GetObjects();
            cursor1 = 0;
            cursor2 = products.Count - 1;
        }

        public void Next()
        {
            if( cursor1 < products.Count )
            {
                cursor1++;
            }
        }

        public bool IsLast()
        {
            return (cursor1 == products.Count);
        }

        public void Previous()
        {
            if( cursor2 > -1 )
            {
                cursor2--;
            }
        }

        public bool IsFirst()
        {
            return (cursor2 == -1);
        }

        public object GetNextItem()
        {
            return products[cursor1];
        }

        public object GetPreviousItem()
        {
            return products[cursor2];
        }
    }
}
