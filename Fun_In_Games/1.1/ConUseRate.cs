using System;
using System.Collections;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace ConsoleApp1
{
    class Program
    {
        //获取系统运行时间毫秒级别
        [DllImport("kernel32.dll")]
        static extern uint GetTickCount();


        //SetThreadAffinityMask 指定hThread 运行在 核心 dwThreadAffinityMask
        [DllImport("kernel32.dll")]
        static extern UIntPtr SetThreadAffinityMask(IntPtr hThread,
        UIntPtr dwThreadAffinityMask);

        //得到当前线程的handler
        [DllImport("kernel32.dll")]
        static extern IntPtr GetCurrentThread();

        static int busyTime = 10;
        static int idleTime = busyTime;
        //设置线程数目
        static int threads = 20;

        public static void ChangeValue(object pid)
        {
            //int core = (int)pid;
            int core = 3;
            int len = 10000000;
            uint[] data = new uint[len];

            //将当前线程绑定到指定的cpu核心上
            SetThreadAffinityMask(GetCurrentThread(), new UIntPtr(SetCpuID(core)));

            uint startTime = GetTickCount();
            Stopwatch stopwatch = new Stopwatch();
            stopwatch.Start();

            for (int i = 0; i < len; ++i)
                data[i] = GetTickCount();


            MakeUsage(50f);
            stopwatch.Stop();
            //Console.WriteLine("运行时间" + stopwatch.ElapsedMilliseconds.ToString());

        }
        //获取cpu的id号
        static ulong SetCpuID(int id)
        {
            ulong cpuid = 0;
            if (id < 0 || id >= System.Environment.ProcessorCount)
            {
                id = 0;
            }
            cpuid |= 1UL << id;

            return cpuid;
        }


        static void Main(string[] args)
        {
            int num = threads;
            Thread[] t = new Thread[num];
            Stopwatch stopwatch = new Stopwatch();

            for (int i = 0; i < num; ++i)
                t[i] = new Thread(new ParameterizedThreadStart(ChangeValue));
            stopwatch.Start();
            for (int i = 0; i < num; ++i)
            {
                t[i].Start(i / 2);
            }

            for (int i = 0; i < num; ++i)
                t[i].Join();
            stopwatch.Stop();
            //Console.WriteLine("总运行时间" + stopwatch.ElapsedMilliseconds.ToString());

            //GetInstanceNameListANDCounterNameList("Processor");
        }

        public static void GetInstanceNameListANDCounterNameList(string CategoryName)
        {
            string[] instanceNames;
            ArrayList counters = new ArrayList();
            PerformanceCounterCategory mycat = new PerformanceCounterCategory(CategoryName);
            try
            {
                instanceNames = mycat.GetInstanceNames();
                if (instanceNames.Length == 0)
                {
                    counters.AddRange(mycat.GetCounters());
                }
                else
                {
                    for (int i = 0; i < instanceNames.Length; i++)
                    {
                        counters.AddRange(mycat.GetCounters(instanceNames[i]));
                    }
                }
                for (int i = 0; i < instanceNames.Length; i++)
                {
                    Console.WriteLine(instanceNames[i]);
                }
                Console.WriteLine("******************************");
                foreach (PerformanceCounter counter in counters)
                {
                    Console.WriteLine(counter.CounterName);
                }
            }
            catch (Exception)
            {
                Console.WriteLine("Unable to list the counters for this category") ;
            }
        }


        static void MakeUsage(float level)//here level belongs to [0,100]
        {
            PerformanceCounter p = new PerformanceCounter();
            p.CategoryName = "Processor";
            p.CounterName = "% Processor Time";
            p.InstanceName = "_Total";

            while (true)
            {
                if (p.NextValue() > level)
                {
                    System.Threading.Thread.Sleep(10);
                }
            }
        }
    }
}

