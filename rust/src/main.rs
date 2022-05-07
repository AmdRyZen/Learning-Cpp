//use std::time::SystemTime;

/*pub struct Stock{
    pub price:f64,
    pub volume:i32,
    pub code:String,
    pub amount:f64,
}
impl Stock{
    fn default()->Self{
        let p =10000.0_f64;
        let v =1_i32;
        Stock{
            price:p,
            volume:v,
            code:String::from("SH600036"),
            amount: p*v as f64,
        }
    }
}

fn main() {
    let now = SystemTime::now();
    let _stock = Stock::default();
    let elapsed = now.elapsed().unwrap().as_nanos();
    println!("cost time :{:?} ",elapsed);
    println!("Hello, world!");
}
*/

use std::sync::{Arc};
use std::sync::atomic::{AtomicUsize, Ordering};
use threadpool::ThreadPool;
use std::sync::mpsc::channel;

fn main() {
    let n_jobs = 30;
    let spinlock = Arc::new(AtomicUsize::new(0));
    let pool = ThreadPool::default();
    let (tx, rx) = channel();
    //let barrier = Arc::new(Barrier::new(n_jobs + 1));
    for i in 0..n_jobs {
        //let barrier = barrier.clone();
        let spinlock_clone = spinlock.clone();
        let tx = tx.clone();
        pool.execute(move|| {
            spinlock_clone.fetch_add(5, Ordering::Relaxed);
            if i < 10 {
                tx.send(1).unwrap();
            } else {
                tx.send(2).unwrap();
            }
            //barrier.wait();
        });
    }
    println!("{:?}", pool.max_count());
    //barrier.wait();
    for rx in rx.iter().take(n_jobs) {
        println!("{:?}", rx);
    }
    pool.join();

    println!("spin : {:?}", spinlock.load(Ordering::Relaxed));
    test_inline();

  /*  let popcnt_output: i32 = hamming_weight(1);
    println!("popcnt_output : {:?}", popcnt_output);

    foo();*/
}

#[inline(always)]
fn test_inline() {
    println!("{:?}", "testInline");
}

/*
#[cfg(any(target_arch = "x86", target_arch = "x86_64"))]
fn foo() {
    unsafe {
        asm!("NOP");
    }
}

#[cfg(any(target_arch = "x86", target_arch = "x86_64"))]
pub fn hamming_weight(n: u32) -> i32 {
    let popcnt_input: usize = n as usize;
    let popcnt_output: usize;
    unsafe {
        asm!(
            "popcnt {popcnt_output}, {popcnt_input}",
            popcnt_input = in(reg) popcnt_input,
            popcnt_output = out(reg) popcnt_output,
        );
    }
    popcnt_output as i32
}*/

#[cfg(test)]
mod test {
    use crate::main;

    #[test]
    fn test_thread_poll() {
        for _ in 0..100000 {
            //unsafe { main(); }
            main();
        }
    }
}