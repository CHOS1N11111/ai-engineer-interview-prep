# 🚀 AI Engineer Interview Prep

> A structured interview-prep repo for **AI Application / LLM / AI Agent Engineering** roles, with C++ coding drills and engineering notes across ML, NLP, LLMs, RAG, Agents, backend, frontend, networking, databases, Docker, Redis, and systems fundamentals.

<p align="center">
  <b>C++ Algorithms</b> · <b>LLM</b> · <b>RAG</b> · <b>Agents</b> · <b>ML/NLP</b> · <b>Backend</b> · <b>Frontend</b> · <b>Systems</b>
</p>

---

## 🧭 Roadmap

```text
Coding Interview
├─ C++ STL & patterns
├─ LeetCode Hot 100 style problems
├─ Mock interview drills
└─ Complexity analysis

AI Engineering
├─ Machine Learning & early NLP
├─ Transformer & LLM fundamentals
├─ Training / Fine-tuning / Inference
├─ RAG, embeddings, vector search
├─ Prompt engineering & AI Agents
└─ Evaluation, safety, performance

Engineering Foundations
├─ Backend / frontend basics
├─ TCP/IP, HTTP, SSE, WebSocket
├─ OS, concurrency, thread pools
├─ Docker, deployment, Nginx
├─ SQL, indexes, transactions
└─ Redis, caching, rate limiting
```

---

## 📚 Repository Structure

| File                                                                          | Purpose                                                                                                                                                                     |
| ----------------------------------------------------------------------------- | --------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| [`llm_ai_agent_interview_concepts.md`](./llm_ai_agent_interview_concepts.md) | Main interview concept notebook: ML, NLP, Transformer, LLM training, fine-tuning, inference, RAG, Agent, backend, frontend, networking, OS, Docker, SQL, Redis, evaluation. |
| [`mock_interview_drills.md`](./mock_interview_drills.md)                     | Mock coding interview drills with problem descriptions, C++ core code, complexity analysis, and follow-up answers.                                                          |
| [`hot100_cpp_solutions.cpp`](./hot100_cpp_solutions.cpp)                     | C++17 implementations for common LeetCode Hot 100 style problems.                                                                                                           |
| [`cpp_pattern_cheatsheet.md`](./cpp_pattern_cheatsheet.md)                   | C++ STL and algorithm pattern cheatsheet.                                                                                                                                   |
| [`pattern_cheatsheet.md`](./pattern_cheatsheet.md)                           | General algorithm pattern cheatsheet.                                                                                                                                       |
| [`hot100_python_solutions.py`](./hot100_python_solutions.py)                 | Python reference solutions kept for comparison.                                                                                                                             |

---

## 🎯 What This Repo Prepares You For

### ✅ Coding Interviews

- Hash table
- Two pointers
- Sliding window
- Prefix sum
- Monotonic stack
- Binary search
- Heap / Top K
- Linked list
- Binary tree
- DFS / BFS
- Backtracking
- Dynamic programming
- Greedy

### ✅ AI / LLM Interviews

- Token, context window, temperature
- Early NLP: TF-IDF, n-gram, HMM, CRF, Word2Vec, RNN, LSTM
- Transformer: self-attention, Q/K/V, mask, RoPE, FlashAttention, KV cache
- LLM training: pretraining, SFT, RLHF, DPO
- Fine-tuning: LoRA, QLoRA, adapters, data quality, checkpoints
- Inference: prefill, decode, KV cache, quantization, batching, serving
- RAG: chunking, embedding, vector DB, hybrid search, reranking
- Agents: tool calling, ReAct, memory, workflow vs agent

### ✅ Engineering Interviews

- Backend API design
- Frontend Chat UI and streaming
- HTTP, HTTPS, CORS, SSE, WebSocket
- Process, thread, coroutine, lock, deadlock
- Docker, Docker Compose, Nginx, deployment debugging
- SQL indexes, transactions, isolation levels, EXPLAIN
- Redis cache, TTL, distributed locks, rate limiting
- Evaluation, observability, safety, cost control

---

## 🗺️ Suggested Study Path

### Phase 1: C++ Coding Basics

1. Read [`cpp_pattern_cheatsheet.md`](./cpp_pattern_cheatsheet.md)
2. Practice [`mock_interview_drills.md`](./mock_interview_drills.md)
3. Compare with [`hot100_cpp_solutions.cpp`](./hot100_cpp_solutions.cpp)

### Phase 2: AI / LLM Concepts

1. Machine learning basics
2. Early NLP and language models
3. Transformer
4. LLM training / fine-tuning / inference
5. RAG and Agent

Main file:

```text
llm_ai_agent_interview_concepts.md
```

### Phase 3: Engineering Depth

Focus on:

- Docker / deployment
- SQL / Redis
- HTTP / SSE / WebSocket
- OS / concurrency
- backend architecture
- observability and evaluation

---

## 🧪 Coding Interview Flow

When solving an algorithm problem:

```text
1. Restate the problem
2. Clarify inputs, outputs, constraints, edge cases
3. Give a brute-force baseline
4. Identify the pattern
5. Explain the invariant
6. Write clean C++ code
7. Test edge cases
8. State time and space complexity
```

Example answer template:

```text
This solution scans the array once, so the time complexity is O(n).
It uses a hash table that may store up to n elements, so the space complexity is O(n).
```

---

## 🧠 AI Engineering Answer Template

When explaining an AI project or concept, use this structure:

```text
1. What problem does it solve?
2. What is the core idea?
3. How is it implemented in engineering?
4. What are the common failure cases?
5. How do we evaluate and optimize it?
```

For example, for RAG:

```text
RAG solves the problem that LLMs may not know private or fresh knowledge.
The system retrieves relevant chunks from an external knowledge base,
then gives them to the LLM as context.
Engineering concerns include chunking, embedding, vector search, reranking,
permission filtering, hallucination control, latency, and evaluation.
```

---

## 📌 High-Frequency Topics Checklist

```text
[ ] Two Sum / 3Sum / Sliding Window
[ ] Linked List reverse / delete nth node
[ ] Binary Tree BFS / DFS / BST
[ ] DP: Coin Change / LIS / LCS
[ ] ML metrics: Precision / Recall / F1 / AUC / MSE / MAE
[ ] Transformer: Q/K/V / mask / RoPE / KV cache
[ ] LLM fine-tuning: SFT / RLHF / DPO / LoRA / QLoRA
[ ] Inference: prefill / decode / batching / quantization
[ ] RAG: chunk / embedding / vector DB / rerank / hybrid search
[ ] Agent: tool calling / ReAct / memory / workflow
[ ] HTTP / SSE / WebSocket / CORS
[ ] Docker / SQL / Redis / concurrency
```

