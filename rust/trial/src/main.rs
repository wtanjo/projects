fn main() {
    let a = 1;
    let b = 2;
    println!("a + b = {}", add(a, b));
}

fn add(a: i32, b: i32) -> i32 {
    a + b
}