//use std::time::Duration;
use std::{thread, env, vec};
use std::sync::{Mutex, Arc};
use once_cell::sync::Lazy;

static MTX_INDEX: Lazy<Arc<Mutex<usize>>> = Lazy::new(|| Arc::new(Mutex::new(0)));
static MTX_VEC: Lazy<Arc<Mutex<Vec<u32>>>> = Lazy::new(|| Arc::new(Mutex::new(vec![])));
 
fn main() {
    let mut handles = vec![];
    let len = get_pass().len();
    for i in 0..2 {
        let handle = thread::spawn(move || {
            let thread_chunk_size = len/2 + i*(len%2); // 0 -> len/2, 1 -> len/2 + len%2
            character_converter(thread_chunk_size, i);
        });
        handles.push(handle);
    }
    for handle in handles {
        handle.join().unwrap();
    }

    let vec = MTX_VEC.lock().unwrap();
    println!("{:?}", vec);

}

fn get_pass() -> String {
    let args: Vec<String> = env::args().collect();
    return String::from(&args[1]);
}

fn character_converter(amount_char_to_process: usize, ind: usize) -> usize { //threadDo
    let pass = get_pass();
    for _i in 0..amount_char_to_process {
        let mut index = MTX_INDEX.lock().unwrap();
        let mut vec = MTX_VEC.lock().unwrap();
        let conversion = convert(pass.chars().nth(*index).unwrap());
        println!("thread{} -> {}", ind, pass.chars().nth(*index).unwrap());
        *index += 1;
        vec.push(conversion);
        std::mem::drop(index);
        std::mem::drop(vec);
        //thread::sleep(Duration::from_millis(10));
    }
    return ind;
}

fn convert(ch: char) -> u32 {
    let conv = ch.to_ascii_lowercase();
    return conv.to_digit(36).unwrap() - 'a'.to_digit(36).unwrap() + 1;

}
