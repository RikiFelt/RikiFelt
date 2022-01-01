using System;

// 建造者模式
namespace BuilderSample
{
    class Product
    {
        public string partA { get; set; }
        public string partB { get; set; }
        public string partC { get; set; }
    }

    abstract class Builder
    {
        protected Product product = new Product();

        public abstract void BuildPartA();
        public abstract void BuildPartB();
        public abstract void BuildPartC();

        public Product GetResult()
        {
            return product;
        }
    }

    class ConcreteBuilder : Builder
    {
        public override void BuildPartA()
        {
            product.partA = "A1";
        }
        public override void BuildPartB()
        {
            product.partB = "B1";
        }
        public override void BuildPartC()
        {
            product.partC = "C1";
        }
    }

    class Director
    {
        private Builder builder;

        public Director( Builder builder )
        {
            this.builder = builder;
        }

        public void SetBuilder( Builder builder )
        {
            this.builder = builder;
        }

        public Product Construct()
        {
            builder.BuildPartA();
            builder.BuildPartB();
            builder.BuildPartC();
            return builder.GetResult();
        }
    }


    class Actor
    {
        public string Type { get; set; }
        public string Sex { get; set; }
        public string Face { get; set; }
        public string Costume { get; set; }
        public string Hairstyle { get; set; }

        public void Display()
        {
            Console.WriteLine("{0}的外观: ", Type);
            Console.WriteLine("性别: {0}", Sex);
            Console.WriteLine("面容: {0}", Face);
            Console.WriteLine("服饰: {0}", Costume);
            Console.WriteLine("发型: {0}", Hairstyle);
        }
    }

    abstract class ActorBuilder
    {
        protected Actor actor = new Actor();

        public abstract void BuildType();
        public abstract void BuildSex();
        public abstract void BuildFace();
        public abstract void BuildCostume();
        public abstract void BuildHairstyle();

        public Actor Construct()
        {
            this.BuildType();
            this.BuildSex();
            this.BuildFace();
            this.BuildCostume();
            this.BuildHairstyle();
            return actor;
        }
    }

    class HeroBuilder : ActorBuilder
    {
        public override void BuildType()
        {
            actor.Type = "英雄";
        }
        public override void BuildSex()
        {
            actor.Sex = "男";
        }
        public override void BuildFace()
        {
            actor.Face = "英俊";
        }
        public override void BuildCostume()
        {
            actor.Costume = "盔甲";
        }
        public override void BuildHairstyle()
        {
            actor.Hairstyle = "飘逸";
        }
    }

    class AngelBuilder : ActorBuilder
    {
        public override void BuildType()
        {
            actor.Type = "天使";
        }
        public override void BuildSex()
        {
            actor.Sex = "女";
        }
        public override void BuildFace()
        {
            actor.Face = "漂亮";
        }
        public override void BuildCostume()
        {
            actor.Costume = "白色连衣裙";
        }
        public override void BuildHairstyle()
        {
            actor.Hairstyle = "单马尾";
        }
    }

    class DevilBuilder : ActorBuilder
    {
        public override void BuildType()
        {
            actor.Type = "恶魔";
        }
        public override void BuildSex()
        {
            actor.Sex = "妖";
        }
        public override void BuildFace()
        {
            actor.Face = "丑陋";
        }
        public override void BuildCostume()
        {
            actor.Costume = "黑衣";
        }
        public override void BuildHairstyle()
        {
            actor.Hairstyle = "光头";
        }
    }
}
