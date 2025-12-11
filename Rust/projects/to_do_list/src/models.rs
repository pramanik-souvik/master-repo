use chrono::NaiveDate;
use serde::{Deserialize, Serialize};

#[derive(Debug, Serialize, Deserialize, Clone, PartialEq)]
pub enum Priority {
    Low,
    Medium,
    High,
}

impl Default for Priority {
    fn default() -> Self {
        Priority::Medium
    }
}

#[derive(Debug, Serialize, Deserialize, Clone)]
pub struct Todo {
    pub task: String,
    pub done: bool,
    pub priority: Priority,
    pub deadline: Option<NaiveDate>,
}
