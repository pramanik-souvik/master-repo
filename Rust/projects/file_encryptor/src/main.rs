use std::fs::{self, File};
use std::io::{self, Read, Write};
use std::env;
use std::path::{Path, PathBuf};

/// Convert password string into byte key vector
fn password_to_key(password: &str) -> Vec<u8> {
    password.bytes().collect()
}

/// XOR encryption/decryption with multi-byte key
fn xor(data: &mut [u8], key: &[u8]) {
    for (i, b) in data.iter_mut().enumerate() {
        *b ^= key[i % key.len()];
    }
}

/// Process a single file
fn process_file(input: &Path, key: &[u8], encrypt: bool, out_dir: &Path) -> io::Result<PathBuf> {
    let mut data = fs::read(input)?;
    xor(&mut data, key);

    let file_name = input.file_name().unwrap();
    let mut output_path = out_dir.join(file_name);

    if encrypt {
        output_path.set_extension(format!("{}.enc", input.extension().unwrap_or_default().to_string_lossy()));
    } else if output_path.extension().unwrap_or_default().to_string_lossy().ends_with("enc") {
        output_path.set_extension("");
    } else {
        output_path.set_extension("dec");
    }

    fs::write(&output_path, &data)?;
    Ok(output_path)
}

/// Recursively process all files in a directory
fn process_dir(dir: &Path, key: &[u8], encrypt: bool, out_dir: &Path) -> io::Result<()> {
    for entry in fs::read_dir(dir)? {
        let entry = entry?;
        let path = entry.path();
        if path.is_dir() {
            process_dir(&path, key, encrypt, out_dir)?;
        } else {
            let out_file = process_file(&path, key, encrypt, out_dir)?;
            println!("Processed: {:?}", out_file);
        }
    }
    Ok(())
}

fn main() {
    let args: Vec<String> = env::args().collect();
    if args.len() < 5 {
        println!("Usage:");
        println!("  encrypt <file_or_dir> <password> <output_dir>");
        println!("  decrypt <file_or_dir> <password> <output_dir>");
        return;
    }

    let operation = &args[1];
    let target = Path::new(&args[2]);
    let password = &args[3];
    let out_dir = Path::new(&args[4]);

    if !out_dir.exists() {
        fs::create_dir_all(out_dir).expect("Failed to create output directory");
    }

    let key = password_to_key(password);

    let result = match operation.as_str() {
        "encrypt" => {
            if target.is_dir() {
                process_dir(target, &key, true, out_dir)
            } else {
                process_file(target, &key, true, out_dir).map(|_| ())
            }
        }
        "decrypt" => {
            if target.is_dir() {
                process_dir(target, &key, false, out_dir)
            } else {
                process_file(target, &key, false, out_dir).map(|_| ())
            }
        }
        _ => {
            eprintln!("Unknown operation: {}", operation);
            return;
        }
    };

    match result {
        Ok(_) => println!("Operation completed successfully!"),
        Err(e) => eprintln!("Error: {}", e),
    }
}