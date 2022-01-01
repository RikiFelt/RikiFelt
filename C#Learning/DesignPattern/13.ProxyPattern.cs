using System;

// 代理模式
namespace ProxySample
{
    class AccessValidator
    {
        public bool Validate( string userId )
        {
            Console.WriteLine("在数据库中验证用户 '" + userId + "' 是否合法用户？");
            if( userId.Equals("杨过") )
            {
                Console.WriteLine(userId + "登录成功");
                return true;
            }
            else
            {
                Console.WriteLine(userId + "登录失败");
                return false;
            }
        }
    }

    class Logger
    {
        public void Log( string userId )
        {
            Console.WriteLine("更新数据库，用户'{0}'查询次数加1！", userId);
        }
    }

    interface Searcher
    {
        string DoSearch( string userId, string keyword );
    }

    class RealSearcher : Searcher
    {
        public string DoSearch( string userId, string keyword )
        {
            Console.WriteLine("用户'{0}'使用关键词'{1}'查询商务信息！", userId, keyword);
            return "返回具体内容";
        }
    }

    class ProxySearcher : Searcher
    {
        private RealSearcher searcher = new RealSearcher();
        private AccessValidator validator;
        private Logger logger;

        public string DoSearch( string userId, string keyword )
        {
            if( Validate(userId) )
            {
                string result = searcher.DoSearch(userId, keyword);
                Log(userId);
                return result;
            }
            else
            {
                return null;
            }
        }

        public bool Validate( string userId )
        {
            validator = new AccessValidator();
            return validator.Validate(userId);
        }

        public void Log( string userId )
        {
            logger = new Logger();
            logger.Log(userId);
        }
    }
}
