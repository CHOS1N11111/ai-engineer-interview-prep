# LLM / AI Agent / 前后端面试高频概念

面向 AI 应用研发、AI Agent 研发、LLM 应用工程实习面试。建议复习方式：先能用自己的话解释概念，再能说出工程落地方案、常见坑和评估指标。

## 1. LLM 基础

### LLM 是什么

LLM，即 Large Language Model，大语言模型。它本质上是一个基于大量文本训练的概率模型，给定上下文 token，预测下一个 token 的概率分布。

面试答法：

> LLM 的核心能力来自大规模预训练，它通过 next token prediction 学到语言模式、知识和一定的推理能力。应用层通常通过 prompt、RAG、工具调用、微调等方式让模型完成具体任务。

常见追问：

- LLM 是不是数据库？
  不是。LLM 参数里压缩了训练数据中的统计规律，但不能像数据库一样保证事实准确、可更新、可追溯。
- 为什么 LLM 会幻觉？
  因为模型目标是生成高概率文本，而不是验证事实。当上下文不足、问题超出知识范围、检索质量差或 prompt 约束弱时，模型可能编造看似合理的内容。

### Token

Token 是模型处理文本的基本单位，可以是字、词、子词、标点或特殊符号。

要点：

- 模型上下文长度按 token 计算，不按字符数计算。
- 中文通常一个字或词片段可能对应一个或多个 token。
- 输入和输出都消耗 token，影响成本和延迟。

面试答法：

> Token 是 LLM 的输入输出单位。工程里需要关注 token 数，因为它决定上下文窗口能放多少内容，也直接影响推理成本、延迟和截断风险。

### Temperature / Top-p

`temperature` 控制随机性，越高输出越发散，越低越稳定。

`top_p` 控制从累计概率前 p 的候选 token 中采样。

使用建议：

- 问答、代码、结构化输出：低温度，如 `0 ~ 0.3`。
- 创意写作、头脑风暴：较高温度，如 `0.7 ~ 1.0`。
- 生产环境要稳定输出时，尽量降低随机性，并增加结构约束。

### 上下文窗口

上下文窗口是模型一次请求能看到的最大 token 数，包括 system prompt、用户输入、历史消息、检索内容和模型输出。

常见问题：

- 上下文太长会增加成本和延迟。
- 无关上下文太多会干扰模型。
- 超过窗口会截断，导致模型丢失关键信息。

工程策略：

- 对历史对话做摘要。
- RAG 只放最相关片段。
- 对文档进行 chunk 和 rerank。
- 把长任务拆成多步。

## 2. 机器学习基础

这一章用于回答“你机器学习基础怎么样”。AI 应用岗不一定要求你推公式很深，但常会问训练流程、过拟合、损失函数、评估指标、常见模型和特征工程。

### 机器学习是什么

机器学习是让计算机从数据中学习规律，并用学到的规律对新样本做预测或决策。

面试答法：

> 传统编程是人写规则，机器学习是给模型数据和目标，让模型自动学习输入到输出之间的映射关系。

例子：

```text
输入：用户历史行为、商品特征
输出：用户是否会点击
模型：从历史样本中学习点击规律
```

### 监督学习、无监督学习、强化学习

监督学习：

- 数据有标签。
- 目标是学习输入到标签的映射。
- 典型任务：分类、回归。

无监督学习：

- 数据没有标签。
- 目标是发现数据内部结构。
- 典型任务：聚类、降维、异常检测。

强化学习：

- 智能体和环境交互。
- 根据 reward 学习策略。
- 典型应用：游戏、机器人、RLHF。

面试答法：

> 监督学习靠标注数据学习预测，无监督学习从无标签数据中找结构，强化学习通过奖励信号学习行动策略。

### 分类和回归

分类：

- 输出离散类别。
- 例子：垃圾邮件识别、情感分类、意图识别。

回归：

- 输出连续数值。
- 例子：房价预测、销量预测、耗时预测。

面试答法：

> 分类预测类别，回归预测连续值。二分类常用交叉熵，回归常用 MSE 或 MAE。

### 训练集、验证集、测试集

训练集：

- 用来训练模型参数。

验证集：

- 用来调超参数、选模型。

测试集：

- 最后评估模型泛化能力。

面试答法：

> 测试集不能参与调参，否则评估结果会偏乐观。验证集用于模型选择，测试集用于最终报告效果。

### 过拟合和欠拟合

过拟合：

- 训练集效果很好，测试集效果差。
- 模型记住了训练数据细节，没有学到泛化规律。

欠拟合：

- 训练集和测试集效果都不好。
- 模型能力不足或特征不够。

解决过拟合：

- 增加数据。
- 数据增强。
- 正则化。
- Dropout。
- Early Stopping。
- 降低模型复杂度。

解决欠拟合：

- 增加特征。
- 增强模型表达能力。
- 训练更久。
- 调大学习率或优化训练策略。

面试答法：

> 过拟合看训练集和验证集差距，欠拟合看两边都差。处理方式一个是增强泛化，一个是增强模型能力。

### Bias 和 Variance

Bias 偏差：

- 模型假设太简单。
- 容易欠拟合。

Variance 方差：

- 模型对训练数据变化太敏感。
- 容易过拟合。

面试答法：

> 偏差高通常说明模型太简单，方差高通常说明模型太复杂。机器学习要在 bias 和 variance 之间做权衡。

### 损失函数

损失函数衡量模型预测和真实标签之间的差距。

常见损失：

- MSE：均方误差，常用于回归。
- MAE：平均绝对误差，回归中对异常值更稳。
- Cross Entropy：交叉熵，常用于分类。
- Hinge Loss：SVM 常用。

面试答法：

> 损失函数定义了模型优化目标。训练过程本质上是在最小化损失函数。

### 梯度下降

梯度下降通过计算损失函数对参数的梯度，沿着损失下降最快的方向更新参数。

简化公式：

```text
参数 = 参数 - learning_rate * gradient
```

常见变体：

- Batch Gradient Descent
- SGD
- Mini-batch SGD
- Momentum
- Adam

面试答法：

> 梯度告诉参数往哪个方向会让 loss 增大，所以我们沿着负梯度方向更新参数，让 loss 下降。

### 学习率

学习率控制每次参数更新的步长。

学习率太大：

- loss 震荡。
- 训练不稳定。
- 可能发散。

学习率太小：

- 收敛慢。
- 可能卡在局部区域。

面试答法：

> 学习率是训练里最重要的超参数之一。太大不稳定，太小收敛慢，所以常用 warmup、decay 或自适应优化器。

### 正则化

正则化用于降低过拟合。

L1 正则：

- 倾向让部分权重变成 0。
- 有特征选择效果。

L2 正则：

- 倾向让权重变小。
- 也叫 weight decay。

面试答法：

> 正则化通过限制模型参数复杂度，降低模型对训练集噪声的记忆，从而提升泛化能力。

### Dropout

Dropout 在训练时随机丢弃一部分神经元，减少神经元之间过强依赖。

作用：

- 缓解过拟合。
- 类似集成多个子网络。

注意：

> Dropout 通常训练时开启，推理时关闭。

### Early Stopping

Early Stopping 是当验证集指标长时间不提升时提前停止训练。

作用：

- 防止继续训练导致过拟合。
- 节省训练成本。

面试答法：

> 如果训练 loss 继续下降，但验证集效果开始变差，说明模型可能过拟合，可以提前停止。

### 特征工程

特征工程是把原始数据转成更适合模型学习的特征。

常见操作：

- 缺失值处理。
- 异常值处理。
- 归一化/标准化。
- 类别特征编码。
- 时间特征提取。
- 文本特征提取。
- 特征交叉。

面试答法：

> 传统机器学习很依赖特征工程。好的特征能显著提升模型效果，尤其在表格数据任务中很重要。

### 归一化和标准化

归一化 Min-Max Scaling：

```text
x' = (x - min) / (max - min)
```

把数值缩放到 `[0, 1]`。

标准化 Standardization：

```text
x' = (x - mean) / std
```

变成均值 0、方差 1。

面试答法：

> 对基于距离或梯度优化的模型，特征尺度差异会影响训练和距离计算，所以常需要归一化或标准化。

### 类别特征编码

常见方法：

- One-hot encoding。
- Label encoding。
- Target encoding。
- Embedding。

注意：

- Label encoding 会引入大小顺序，树模型通常还能接受，线性模型要谨慎。
- 高基数类别 one-hot 会导致维度爆炸。

### 数据泄漏

数据泄漏是训练时使用了预测时无法获得的信息，导致离线指标虚高。

例子：

- 用未来数据预测过去。
- 标准化时用全量数据计算均值方差。
- 用户标签间接出现在特征里。

面试答法：

> 数据泄漏会让模型在测试集上看起来很好，但上线后效果崩掉。做特征和划分数据时必须模拟真实预测场景。

### 类别不平衡

类别不平衡指某些类别样本远多于其他类别。

解决方式：

- 重采样：过采样少数类、欠采样多数类。
- 类别权重。
- 调整阈值。
- 使用更合适指标，如 F1、AUC、PR-AUC。

面试答法：

> 类别极不平衡时，accuracy 可能没有意义。例如 99% 都是负样本，模型全预测负样本也有 99% accuracy。

### 常见评估指标：分类

混淆矩阵：

```text
TP：预测正，实际正
FP：预测正，实际负
FN：预测负，实际正
TN：预测负，实际负
```

速记：

```text
TP = 预测为正，且预测对了
FP = 预测为正，但预测错了
FN = 预测为负，但预测错了
TN = 预测为负，且预测对了
```

其中 `T/F` 看预测对不对，`P/N` 看模型预测成什么。

Accuracy：

```text
(TP + TN) / 全部样本
```

Precision：

```text
TP / (TP + FP)
```

预测为正的样本里，有多少是真的正。

Recall：

```text
TP / (TP + FN)
```

真实为正的样本里，有多少被找出来。

F1：

```text
2 * Precision * Recall / (Precision + Recall)
```

面试答法：

> Precision 关注预测出来的正样本准不准，Recall 关注真实正样本有没有找全，F1 是两者的调和平均。

### ROC-AUC 和 PR-AUC

ROC-AUC：

- 衡量模型区分正负样本的能力。
- 类别较均衡时常用。

PR-AUC：

- Precision-Recall 曲线下面积。
- 类别极不平衡时更有参考价值。

面试答法：

> 类别极不平衡时，PR-AUC 往往比 ROC-AUC 更敏感，因为它更关注正类识别质量。

### 常见评估指标：回归

MSE，Mean Squared Error，均方误差：

```text
mean((y - y_pred)^2)
```

含义：预测值和真实值之差的平方，再求平均。因为误差会被平方，所以对大误差惩罚更重。

RMSE，Root Mean Squared Error，均方根误差：

```text
sqrt(MSE)
```

单位和原目标一致。

MAE，Mean Absolute Error，平均绝对误差：

```text
mean(abs(y - y_pred))
```

含义：预测值和真实值之差取绝对值，再求平均。相比 MSE，MAE 对异常值更稳，不会因为平方把大误差放得特别大。

R²：

- 衡量模型解释方差的能力。

### 逻辑回归

逻辑回归常用于二分类。

核心：

- 线性模型输出一个 score。
- 通过 sigmoid 映射成概率。

面试答法：

> 逻辑回归虽然名字里有回归，但常用于分类。它输出属于正类的概率，训练时常用交叉熵损失。

### 决策树

决策树通过一系列 if-else 规则进行划分。

优点：

- 可解释性强。
- 能处理非线性关系。
- 对特征缩放不敏感。

缺点：

- 容易过拟合。
- 对数据扰动敏感。

常见划分指标：

- 信息增益。
- 信息增益率。
- Gini 指数。

### 随机森林

随机森林是多棵决策树的集成。

特点：

- Bagging 思想。
- 每棵树用随机样本和随机特征训练。
- 降低单棵树的方差。

面试答法：

> 随机森林通过训练多棵差异化的树并投票或平均，降低过拟合，提高泛化能力。

### GBDT / XGBoost / LightGBM

GBDT：

- Boosting 思想。
- 后一棵树拟合前面模型的残差或梯度方向。

XGBoost：

- 工程优化强。
- 加入正则化。
- 支持并行和缺失值处理。

LightGBM：

- 训练速度快。
- 适合大规模表格数据。
- 使用 histogram 和 leaf-wise 生长策略。

面试答法：

> 随机森林是 bagging，主要降低方差；GBDT 是 boosting，逐步修正前面模型错误，通常表格数据上效果很强。

### SVM

SVM 的目标是找到一个最大间隔超平面，把不同类别分开。

关键词：

- 最大间隔。
- 支持向量。
- 核函数。

面试答法：

> SVM 通过最大化分类间隔提升泛化能力，核函数可以把非线性问题映射到高维空间处理。

### KNN

KNN 根据距离最近的 k 个样本投票或平均。

特点：

- 训练简单。
- 推理慢。
- 对特征尺度敏感。

面试答法：

> KNN 是懒惰学习，训练阶段几乎不做事，预测时才计算距离，所以数据量大时推理成本高。

### 朴素贝叶斯

朴素贝叶斯基于贝叶斯公式，并假设特征之间条件独立。

常见应用：

- 文本分类。
- 垃圾邮件识别。

面试答法：

> 朴素贝叶斯假设特征条件独立，这个假设很强，但在文本分类等任务上简单高效。

### K-Means

K-Means 是无监督聚类算法。

流程：

1. 随机初始化 k 个聚类中心。
2. 每个样本分配到最近中心。
3. 更新聚类中心。
4. 重复直到收敛。

注意：

- 需要预先指定 k。
- 对初始点敏感。
- 对异常值敏感。

### PCA

PCA 是常见降维方法，目标是找到能保留最大方差的方向。

用途：

- 降维。
- 可视化。
- 去噪。

面试答法：

> PCA 通过线性变换把数据投影到方差最大的方向上，用更少维度保留主要信息。

### 交叉验证

K 折交叉验证：

- 把数据分成 K 份。
- 每次用 K-1 份训练，1 份验证。
- 最后取平均指标。

作用：

- 更稳定评估模型效果。
- 数据量较小时尤其有用。

### 超参数调优

超参数是训练前设置的参数，不是模型自己学出来的。

例子：

- 学习率。
- 树深度。
- 正则化系数。
- batch size。
- kNN 的 k。

调参方法：

- Grid Search。
- Random Search。
- Bayesian Optimization。

### 机器学习项目流程

推荐回答框架：

1. 明确任务和指标。
2. 收集和理解数据。
3. 数据清洗。
4. 特征工程。
5. 划分训练/验证/测试集。
6. 选择 baseline 模型。
7. 训练和调参。
8. 离线评估。
9. 上线灰度。
10. 监控数据漂移和效果。

### 数据漂移

数据漂移是线上数据分布和训练数据分布发生变化。

例子：

- 用户行为变化。
- 新业务场景出现。
- 节假日影响。
- 数据采集逻辑变化。

解决：

- 监控特征分布。
- 定期重训。
- 引入线上反馈。
- 做模型回滚。

### 机器学习和深度学习的区别

传统机器学习：

- 更依赖人工特征工程。
- 常用于表格数据。
- 模型相对轻量。

深度学习：

- 自动学习表示。
- 适合图像、语音、文本等非结构化数据。
- 需要更多数据和算力。

面试答法：

> 传统机器学习强在表格数据和可解释性，深度学习强在表示学习和非结构化数据处理。

### 和 LLM 应用的关系

机器学习基础在 LLM 应用中仍然重要：

- RAG 评估需要 precision、recall、hit rate。
- reranker 本质是排序模型。
- 用户意图识别可以是分类任务。
- 文档质量评分可以是回归或分类任务。
- 推荐 prompt、路由模型、风控审核都可能用传统 ML。

面试答法：

> LLM 应用不是只调用大模型。很多模块仍然会用传统机器学习，比如意图分类、排序、风控、质量评估和用户反馈建模。

### 高频开放题：怎么判断模型是否过拟合

答题框架：

- 训练集指标很好。
- 验证集/测试集指标明显差。
- 训练 loss 下降，但验证 loss 上升。
- 可以用正则化、早停、增加数据、降低模型复杂度处理。

### 高频开放题：Precision 和 Recall 怎么取舍

答题框架：

- 看业务更怕误报还是漏报。
- 垃圾邮件：误杀正常邮件代价高，precision 要高。
- 疾病筛查：漏掉患者代价高，recall 要高。
- 最终通过阈值调整权衡。

### 高频开放题：线上效果差怎么办

答题框架：

1. 检查训练/线上特征是否一致。
2. 检查是否有数据漂移。
3. 检查样本标注质量。
4. 分析错误案例。
5. 重新做特征或补数据。
6. 调整模型和阈值。
7. 做灰度和回归评估。

## 3. 早期 NLP 与传统语言模型

这一章用于回答“在大模型之前，NLP 是怎么做的”。面试时不一定深挖公式，但理解传统 NLP 到 LLM 的演进脉络，会让你讲 Transformer 和大模型时更有层次。

### 早期 NLP 主要做什么

早期 NLP 任务包括：

- 分词
- 词性标注
- 命名实体识别
- 文本分类
- 情感分析
- 机器翻译
- 信息抽取
- 问答系统
- 文本相似度

面试答法：

> 早期 NLP 更依赖人工特征、统计模型和任务专用模型。后来深度学习引入词向量、RNN、seq2seq、attention，最后 Transformer 和预训练语言模型成为主流。

### 分词

分词是把文本切成词或子词。

中文为什么需要分词：

- 英文天然有空格。
- 中文句子没有显式词边界。

例子：

```text
我喜欢自然语言处理
-> 我 / 喜欢 / 自然语言处理
```

常见方法：

- 基于词典的最大匹配。
- HMM、CRF 等序列标注。
- 神经网络分词。
- 现代 LLM 常用 BPE、SentencePiece 等子词切分。

### One-hot 表示

One-hot 用一个很长的向量表示词，词表里每个词对应一个位置。

例子：

```text
词表：[我, 喜欢, NLP]
我 -> [1, 0, 0]
喜欢 -> [0, 1, 0]
NLP -> [0, 0, 1]
```

缺点：

- 维度很高。
- 向量稀疏。
- 无法表达词语相似性。

面试答法：

> One-hot 只能表示词是否相同，不能表示语义相似。例如“猫”和“狗”的 one-hot 距离和“猫”和“汽车”一样远。

### Bag of Words 词袋模型

词袋模型只统计文本中出现了哪些词和出现次数，不考虑词序。

例子：

```text
文本：我 喜欢 NLP
特征：我=1, 喜欢=1, NLP=1
```

优点：

- 简单。
- 适合传统文本分类 baseline。

缺点：

- 不考虑词序。
- 语义表达弱。
- 稀疏高维。

### TF-IDF

TF-IDF 用来衡量一个词对某篇文档的重要性。

TF：

- Term Frequency，词频。
- 一个词在当前文档中出现越多，TF 越高。

IDF：

- Inverse Document Frequency，逆文档频率。
- 一个词在越少文档中出现，IDF 越高。

直观理解：

> “的”“是”这种词出现很多，但区分度低；某个专业词在少数文档中频繁出现，往往更能代表文档主题。

面试答法：

> TF-IDF 既考虑词在当前文档中的频率，也考虑词在整个语料中的稀有程度，适合关键词提取、搜索和传统文本分类。

### N-gram

N-gram 是连续 n 个词或字符组成的片段。

例子：

```text
句子：我 喜欢 NLP
unigram: 我, 喜欢, NLP
bigram: 我 喜欢, 喜欢 NLP
trigram: 我 喜欢 NLP
```

作用：

- 引入局部词序信息。
- 可用于传统语言模型、文本分类、拼写纠错。

缺点：

- n 越大，组合越稀疏。
- 泛化能力有限。

### 传统语言模型

语言模型的目标是给一个句子计算概率，或者根据前文预测下一个词。

公式直观理解：

```text
P(我 喜欢 NLP) = P(我) * P(喜欢 | 我) * P(NLP | 我 喜欢)
```

N-gram 语言模型做了马尔可夫假设：

> 当前词只依赖前面有限的 n-1 个词。

例如 bigram：

```text
P(w_i | w_1 ... w_{i-1}) ≈ P(w_i | w_{i-1})
```

面试答法：

> 传统 n-gram 语言模型用统计频率估计词序列概率，简单有效，但上下文窗口短，数据稀疏严重。

### 平滑 Smoothing

N-gram 会遇到没见过的词组合，概率可能变成 0。平滑用于给未出现过的组合分配一点概率。

常见方法：

- Add-one smoothing。
- Good-Turing。
- Kneser-Ney。

面试答法：

> 平滑是为了解决数据稀疏问题，避免未见过的 n-gram 概率为 0。

### HMM

HMM，即 Hidden Markov Model，隐马尔可夫模型。

组成：

- 隐状态：看不见的标签，比如词性、分词标签。
- 观测值：看得见的词或字。
- 转移概率：状态到状态的概率。
- 发射概率：状态生成观测的概率。

应用：

- 分词。
- 词性标注。
- 简单命名实体识别。

面试答法：

> HMM 用隐状态建模序列标签，用观测值表示输入文本。它假设当前状态主要依赖前一个状态。

### CRF

CRF，即 Conditional Random Field，条件随机场，常用于序列标注。

相比 HMM：

- HMM 是生成式模型。
- CRF 是判别式模型。
- CRF 能使用更丰富的上下文特征。

应用：

- 分词。
- 词性标注。
- 命名实体识别。

面试答法：

> CRF 常用于序列标注，它直接建模给定输入序列时标签序列的条件概率，能利用丰富特征，早期 NER 中很常见。

### Word Embedding

词向量把词映射成低维稠密向量，语义相近的词向量距离更近。

相比 one-hot：

- 维度低。
- 稠密。
- 能表达语义相似性。

例子：

```text
king - man + woman ≈ queen
```

面试答法：

> 词向量解决了 one-hot 稀疏和无法表达语义的问题，把词放到连续向量空间里，语义相似的词距离更近。

### Word2Vec

Word2Vec 是经典词向量方法。

两种结构：

- CBOW：根据上下文预测中心词。
- Skip-gram：根据中心词预测上下文。

面试答法：

> CBOW 用上下文预测当前词，训练快；Skip-gram 用当前词预测上下文，对低频词效果通常更好。

### GloVe

GloVe 利用全局词共现统计学习词向量。

对比 Word2Vec：

- Word2Vec 更偏局部上下文预测。
- GloVe 更强调全局共现矩阵。

面试答法：

> GloVe 的核心是利用全局词共现信息，让词向量反映词与词在语料中的共现关系。

### 静态词向量的问题

Word2Vec、GloVe 属于静态词向量。

问题：

- 一个词只有一个向量。
- 无法处理一词多义。

例子：

```text
苹果 很甜
苹果 发布了 新手机
```

这里“苹果”含义不同，但静态词向量相同。

解决方向：

> ELMo、BERT、GPT 这类上下文相关表示，会根据上下文动态生成词表示。

### RNN

RNN，即 Recurrent Neural Network，循环神经网络，适合处理序列数据。

核心思想：

```text
当前隐藏状态 = f(当前输入, 上一步隐藏状态)
```

优点：

- 能处理变长序列。
- 能利用前文信息。

缺点：

- 难以并行。
- 长距离依赖困难。
- 容易梯度消失或爆炸。

### LSTM / GRU

LSTM 和 GRU 是改进版 RNN，用门控机制缓解长距离依赖问题。

LSTM 常见门：

- 输入门。
- 遗忘门。
- 输出门。

GRU：

- 结构比 LSTM 简化。
- 参数更少。

面试答法：

> LSTM 通过门控机制控制信息保留和遗忘，比普通 RNN 更能处理长距离依赖，但仍然不如 Transformer 容易并行。

### Seq2Seq

Seq2Seq，即 Sequence to Sequence，输入一个序列，输出另一个序列。

典型结构：

```text
Encoder -> Context Vector -> Decoder
```

应用：

- 机器翻译。
- 文本摘要。
- 对话生成。

问题：

- 把整个输入压缩到一个固定长度向量，长句信息容易丢失。

### Attention 机制

Attention 允许 decoder 在生成每个词时，动态关注输入序列的不同位置。

解决的问题：

- Seq2Seq 固定向量瓶颈。
- 长序列信息丢失。

面试答法：

> Attention 让模型生成每个输出 token 时都能看输入的不同部分，不必把所有信息压缩进一个固定向量。

### Transformer 为什么取代 RNN

RNN 的问题：

- 顺序计算，难并行。
- 长距离依赖困难。
- 训练效率低。

Transformer 的优势：

- Self-attention 能直接建模任意 token 间关系。
- 更容易并行训练。
- 适合大规模数据和算力。

面试答法：

> Transformer 取代 RNN 的关键原因是并行效率和长距离依赖建模能力。它更适合大规模训练，因此成为现代 LLM 的基础。

### 传统 NLP 和 LLM 的区别

传统 NLP：

- 每个任务通常单独建模。
- 依赖特征工程。
- 模型能力较窄。
- 泛化能力有限。

LLM：

- 统一成文本生成或指令跟随。
- 通过预训练获得通用能力。
- 可以 zero-shot / few-shot。
- 可结合 RAG、工具调用完成复杂任务。

面试答法：

> 传统 NLP 更像为每个任务训练一个专用模型，LLM 则用一个通用模型通过 prompt 和上下文适配不同任务。

### 早期 NLP 到 LLM 的演进

可以这样讲：

```text
规则和词典
-> 统计机器学习：TF-IDF、HMM、CRF、n-gram
-> 静态词向量：Word2Vec、GloVe
-> 深度序列模型：RNN、LSTM、Seq2Seq
-> Attention
-> Transformer
-> 预训练语言模型：BERT、GPT
-> 指令微调和 Agent 应用
```

面试答法：

> NLP 的主线是从人工特征到表示学习，再到大规模预训练。Transformer 之后，很多任务都被统一成基于上下文的生成和理解问题。

### 高频开放题：TF-IDF 和 Embedding 有什么区别

答题框架：

- TF-IDF 是稀疏统计特征。
- Embedding 是稠密语义向量。
- TF-IDF 更关注词频和区分度。
- Embedding 更能表达语义相似。
- 搜索中可以结合 BM25/TF-IDF 和向量检索做 hybrid search。

### 高频开放题：为什么 RNN 不如 Transformer 适合大模型

答题框架：

- RNN 必须按时间步顺序计算，难并行。
- 长距离依赖容易衰减。
- Transformer self-attention 可以直接连接任意位置。
- Transformer 更适合 GPU 并行和大规模训练。

### 高频开放题：BERT 和 GPT 有什么区别

答题框架：

- BERT 是 encoder-only，更适合理解类任务。
- GPT 是 decoder-only，自回归生成，更适合生成类任务。
- BERT 常用 Masked Language Modeling。
- GPT 常用 next token prediction。
- 现代对话大模型多采用 GPT 类 decoder-only 架构。

## 4. Transformer 高频概念

Transformer 是现代大语言模型的核心架构。面试时不一定要手推所有公式，但必须能讲清楚：attention 在做什么，Q/K/V 是什么，为什么能并行，为什么需要 mask，BERT 和 GPT 架构有什么区别，以及工程上为什么会关注 KV cache、GQA、长上下文。

### Transformer 为什么适合 LLM

Transformer 的核心优势：

- Self-attention 能直接建模任意两个 token 之间的关系。
- 相比 RNN，更容易并行训练。
- 能通过堆叠层数和扩大参数量获得强表达能力。
- 适合大规模语料、大规模 GPU 并行训练。

面试答法：

> Transformer 相比 RNN 不需要按时间步顺序处理 token，训练并行性更好；self-attention 能让每个 token 直接关注上下文中任意位置的信息，所以更适合大规模语言模型。

### Transformer 基本结构

一个 Transformer block 通常包含：

```text
输入 hidden states
-> Multi-Head Self-Attention
-> 残差连接
-> LayerNorm
-> Feed Forward Network
-> 残差连接
-> LayerNorm
```

不同模型可能是 Pre-LN 或 Post-LN：

- Post-LN：先残差，再 LayerNorm，早期 Transformer 常见。
- Pre-LN：先 LayerNorm，再进入 attention/FFN，现代大模型更常见，训练更稳定。

面试答法：

> Transformer block 主要由 attention 和 FFN 两部分组成。attention 负责 token 间信息交互，FFN 负责对每个位置做非线性变换，残差和 LayerNorm 保证深层网络训练稳定。

### Self-Attention

Self-attention 的作用：

> 对序列中的每个 token，根据它和其他 token 的相关性，聚合上下文信息。

简化公式：

```text
Attention(Q, K, V) = softmax(QK^T / sqrt(d_k)) V
```

直观理解：

- `Q`：Query，当前 token 想找什么信息。
- `K`：Key，每个 token 提供的索引。
- `V`：Value，每个 token 真正提供的内容。
- `QK^T`：计算当前 token 和其他 token 的相关性。
- `softmax`：把相关性变成权重。
- 加权求和 `V`：得到融合上下文后的表示。

面试答法：

> Q 和 K 算相似度，softmax 得到注意力权重，再对 V 加权求和。这样每个 token 都能从上下文中取到自己需要的信息。

### Q / K / V 从哪里来

Q、K、V 都是由输入 hidden states 经过不同线性层变换得到的。

```text
Q = XWq
K = XWk
V = XWv
```

同一个 token 会生成自己的 Q、K、V：

- Q 用来主动查询别人。
- K 用来被别人匹配。
- V 用来提供实际信息。

工程上常见投影层名字：

```text
q_proj
k_proj
v_proj
o_proj
```

LoRA 微调时，经常会把 adapter 加在这些投影层上。

### 为什么除以 sqrt(d_k)

`QK^T` 的值会随着维度 `d_k` 增大而变大。如果不缩放，softmax 可能变得很尖锐，导致梯度不稳定。

所以使用：

```text
QK^T / sqrt(d_k)
```

面试答法：

> 除以 sqrt(d_k) 是为了避免点积值过大导致 softmax 饱和，从而提升训练稳定性。

### Attention Mask

Mask 用来控制哪些 token 可以被看到。

常见 mask：

- Padding mask：忽略 padding token。
- Causal mask：防止当前位置看到未来 token。

GPT 类模型使用 causal mask：

```text
生成第 i 个 token 时，只能看 1 到 i-1 的 token，不能偷看未来。
```

BERT 类模型通常不是 causal mask：

```text
它可以双向看上下文，所以适合理解任务。
```

面试答法：

> Mask 是控制注意力可见范围的。GPT 做自回归生成，需要 causal mask 防止看到未来；BERT 做理解任务，可以双向看上下文。

### Multi-Head Attention

Multi-head attention 是把 hidden state 分成多个 head 并行做 attention。

为什么需要多头：

- 不同 head 可以关注不同关系。
- 有的 head 关注语法。
- 有的 head 关注实体。
- 有的 head 关注长距离依赖。

流程：

```text
X -> 多组 Q/K/V -> 多个 attention head -> concat -> output projection
```

面试答法：

> 单个 attention head 表达能力有限，多头机制让模型从多个子空间学习不同的关注模式，最后再融合。

### MHA / MQA / GQA

MHA，Multi-Head Attention：

- 每个 head 有自己的 Q/K/V。
- 效果好，但 KV cache 占用大。

MQA，Multi-Query Attention：

- 多个 query head 共享同一组 K/V。
- KV cache 更小。
- 推理更省显存、更快。

GQA，Grouped-Query Attention：

- 把 query heads 分组，每组共享 K/V。
- 介于 MHA 和 MQA 之间。
- 现代 LLM 很常见。

工程意义：

> 推理时 KV cache 是显存大头之一。MQA/GQA 通过减少 K/V head 数量，降低 KV cache 显存，提高长上下文和高并发能力。

面试答法：

> MHA 效果强但 KV cache 大；MQA/GQA 是工程上为了降低推理显存和提升吞吐的 attention 变体。

### Feed Forward Network

FFN 是 Transformer block 中除 attention 之外的另一大模块。

它通常对每个 token 位置独立做两层或多层 MLP：

```text
FFN(x) = W2 activation(W1 x)
```

作用：

- attention 负责 token 间信息交互。
- FFN 负责对每个 token 的表示做非线性变换和特征提取。

现代 LLM 常见激活：

- GELU。
- SwiGLU。

工程上：

- FFN 参数量通常很大。
- LoRA 也可以加到 `up_proj`、`down_proj`、`gate_proj`。

### 残差连接

残差连接形式：

```text
x = x + sublayer(x)
```

作用：

- 缓解深层网络梯度消失。
- 让信息更容易跨层传递。
- 训练更稳定。

面试答法：

> 残差连接让模型在深层网络中保留原始信息，也让梯度更容易传播，是训练深层 Transformer 的关键结构。

### LayerNorm

LayerNorm 对每个 token 的 hidden dimension 做归一化。

作用：

- 稳定训练。
- 减少激活分布变化。
- 帮助深层网络收敛。

BatchNorm vs LayerNorm：

- BatchNorm 依赖 batch 维度，CV 中常见。
- LayerNorm 不依赖 batch size，更适合 NLP 变长序列和小 batch 场景。

面试答法：

> NLP 里常用 LayerNorm，因为文本 batch 长度不固定，而且大模型训练中每卡 batch 可能很小，LayerNorm 更稳定。

### Position Encoding

Self-attention 本身不包含顺序信息，所以需要位置编码。

常见方式：

- Sinusoidal position encoding：原始 Transformer 使用。
- Learned position embedding：可学习绝对位置。
- Relative position embedding：建模相对距离。
- RoPE：旋转位置编码，现代 LLM 常见。
- ALiBi：用 attention bias 表示距离。

面试答法：

> Attention 只看 token 间相关性，本身不知道顺序，所以需要位置编码告诉模型 token 的位置信息。

### RoPE

RoPE，即 Rotary Position Embedding，旋转位置编码。

直观理解：

> RoPE 把位置信息通过旋转方式注入 Q/K，让 attention 在计算相似度时感知相对位置信息。

为什么常见：

- 适合 decoder-only LLM。
- 对相对位置建模友好。
- 长上下文扩展时经常会讨论 RoPE scaling。

工程相关：

- 长上下文模型可能使用 RoPE scaling。
- 位置编码策略会影响模型外推到更长上下文的能力。

### Encoder-only / Decoder-only / Encoder-Decoder

Encoder-only：

- 代表：BERT。
- 双向 attention。
- 适合理解任务，如分类、匹配、NER。

Decoder-only：

- 代表：GPT 系列。
- causal attention。
- 适合自回归生成。
- 现代 LLM 主流架构。

Encoder-Decoder：

- 代表：T5、原始 Transformer 翻译模型。
- encoder 理解输入，decoder 生成输出。
- 适合翻译、摘要等 seq2seq 任务。

面试答法：

> BERT 是 encoder-only，适合理解；GPT 是 decoder-only，适合生成；T5 是 encoder-decoder，适合输入到输出的转换任务。

### BERT 和 GPT 的区别

BERT：

- Encoder-only。
- 双向上下文。
- 训练目标是 Masked Language Modeling。
- 适合理解类任务。

GPT：

- Decoder-only。
- 只能看左侧上下文。
- 训练目标是 Next Token Prediction。
- 适合生成类任务。

面试答法：

> BERT 双向看上下文，适合理解；GPT 自回归从左到右生成，适合对话和文本生成。现代大语言模型大多是 GPT 类 decoder-only 架构。

### Transformer 的复杂度

Self-attention 对序列长度 `n` 的复杂度通常是：

```text
时间复杂度：O(n^2)
空间复杂度：O(n^2)
```

原因：

> 每个 token 都要和其他 token 计算注意力分数，所以 attention matrix 是 n x n。

工程影响：

- 上下文越长，attention 计算越贵。
- 长上下文会显著增加显存和延迟。
- 推理时还会受到 KV cache 影响。

常见优化方向：

- FlashAttention。
- Sparse Attention。
- Sliding Window Attention。
- Long-context RoPE scaling。
- RAG 减少塞入上下文的 token。

### FlashAttention

FlashAttention 是一种高效 attention 实现。

它不是改变 attention 公式，而是优化计算和显存访问方式。

核心收益：

- 减少显存读写。
- 提升 attention 计算速度。
- 支持更长序列或更大 batch。

面试答法：

> FlashAttention 不是新的模型结构，而是 attention 的高效实现，主要通过优化 GPU memory IO 提升速度和降低显存占用。

### 长上下文为什么难

长上下文困难来自：

- attention 计算随长度平方增长。
- KV cache 随上下文长度增长。
- prompt 太长导致首 token 慢。
- 无关信息太多会干扰模型。
- 位置编码外推可能变差。

工程策略：

- RAG 检索相关片段。
- 对历史对话做摘要。
- 限制 top-k chunk 数量。
- 使用长上下文模型。
- 使用 sliding window 或 sparse attention。

### Transformer 和 RNN 的对比

RNN：

- 顺序计算。
- 难并行。
- 长距离依赖容易衰减。

Transformer：

- 并行计算。
- attention 直接连接任意位置。
- 更适合大规模训练。

代价：

- attention 对长序列成本高。
- 需要位置编码。
- 推理时 KV cache 占用显存。

### 工程上为什么关注 KV Cache

训练时主要关注 attention 计算和激活显存。

推理时特别关注 KV cache：

- 每生成一个 token 都要用历史 K/V。
- 不缓存会重复计算历史。
- 缓存后速度快，但显存占用大。

这也是为什么：

- GQA/MQA 很重要。
- PagedAttention 很重要。
- 长上下文会降低并发。

### 高频开放题：为什么 Transformer 能并行而 RNN 不行

答题框架：

- RNN 的第 t 步依赖第 t-1 步 hidden state，必须顺序计算。
- Transformer 的 self-attention 可以一次性计算所有 token 间关系。
- 训练时 Transformer 更适合 GPU 并行。

### 高频开放题：attention 和 RAG 里的 attention 是一回事吗

答题框架：

- Transformer attention 是模型内部机制，用 Q/K/V 在 token 间做加权聚合。
- RAG 里的“关注相关文档”通常是比喻，本质是检索和上下文拼接。
- 两者都和“相关性”有关，但发生在不同层面。

### 高频开放题：为什么现代 LLM 多用 decoder-only

答题框架：

- decoder-only 天然适合 next token prediction。
- 预训练目标和生成式应用一致。
- 架构简单，scaling 效果好。
- 对话、代码、工具调用都可以统一成自回归生成。

### 高频开放题：Transformer 的主要瓶颈是什么

答题框架：

- 长序列 attention 是 O(n^2)。
- 推理时 KV cache 占显存。
- 大模型参数量导致显存和计算成本高。
- 工程上用 FlashAttention、GQA、PagedAttention、量化、RAG 等方式优化。

## 5. 大模型训练

这一章用于回答“你了解大模型是怎么训练出来的吗”。实习面试会考察你是否理解预训练、数据、loss、显存和分布式训练这些基础概念。

### 大模型生命周期

典型流程：

```text
数据收集 -> 数据清洗 -> Tokenization -> 预训练 -> 指令微调 -> 对齐训练 -> 评估 -> 推理部署 -> 监控迭代
```

面试答法：

> 大模型通常先通过大规模语料做预训练，学习通用语言能力；再通过指令微调让模型学会按人类指令回答；最后通过偏好对齐让回答更符合人类偏好和安全要求。应用层还会结合 RAG、工具调用和评估体系来落地。

### 预训练 Pretraining

预训练是用海量无标注文本训练模型的阶段。常见目标是 next token prediction，即根据前文预测下一个 token。

核心特点：

- 数据量极大。
- 训练成本最高。
- 学到通用语言能力和世界知识。
- 通常不是普通应用团队从零做。

面试答法：

> 预训练阶段让模型学会语言规律和通用知识。它不是针对某个具体任务，而是通过预测下一个 token 获得通用能力。

### 训练数据

数据来源：

- 网页文本
- 书籍
- 代码
- 论文
- 对话数据
- 领域文档

数据处理：

- 去重
- 去低质量内容
- 去隐私和敏感信息
- 语言识别
- 格式清洗
- 毒性和安全过滤
- 文档切分

面试答法：

> 大模型效果很大程度取决于数据质量。高质量、去重、覆盖广的数据比单纯堆数据量更重要。

### Tokenizer

Tokenizer 把文本切成 token id，模型实际处理的是 token id 序列。

常见算法：

- BPE
- WordPiece
- SentencePiece

影响：

- 决定词表大小。
- 影响中文、英文、代码的切分效率。
- 影响上下文窗口利用率。

面试答法：

> Tokenizer 是文本和模型之间的桥。不同 tokenizer 会导致同一句话 token 数不同，从而影响成本、上下文长度和模型效果。

### Loss

语言模型预训练常用交叉熵损失。

直观理解：

> 如果模型给正确下一个 token 的概率越高，loss 越低；如果模型预测错得离谱，loss 越高。

面试答法：

> LLM 训练时通常对每个位置预测下一个 token，用交叉熵衡量预测分布和真实 token 的差距。

### Batch Size / Epoch / Learning Rate

Batch Size：

- 每次参数更新使用多少样本。
- 大 batch 更稳定，但显存需求更高。

Epoch：

- 训练数据被完整看过几轮。
- 大模型预训练通常更关注 token 数，不一定用传统 epoch 表达。

Learning Rate：

- 参数更新步长。
- 太大容易不稳定，太小收敛慢。

面试答法：

> 学习率决定每步更新幅度，是训练稳定性的关键超参数。大模型训练通常会用 warmup 和 learning rate decay。

### 训练中的显存主要花在哪里

显存占用主要来自：

- 模型参数
- 梯度
- 优化器状态
- 激活值
- KV cache，推理阶段更明显

面试答法：

> 训练显存不仅是模型参数，还包括梯度、优化器状态和中间激活。使用 Adam 时优化器状态通常会带来很大额外显存。

### 混合精度训练

常见精度：

- FP32
- FP16
- BF16

混合精度训练用较低精度加速计算和减少显存，同时保留必要的数值稳定性。

面试答法：

> 混合精度能降低显存和提升吞吐，但要注意数值溢出和稳定性。BF16 动态范围更大，训练大模型时更稳定。

### 分布式训练

为什么需要：

- 单卡放不下模型。
- 单卡训练太慢。

常见并行方式：

- 数据并行：每张卡放一份模型，处理不同数据。
- 张量并行：把单层矩阵计算切到多张卡。
- 流水线并行：把不同层放到不同卡。
- ZeRO：优化参数、梯度、优化器状态的分片存储。

面试答法：

> 数据并行解决吞吐，模型并行解决模型太大放不下。ZeRO 通过切分优化器状态、梯度和参数来降低单卡显存压力。

## 6. 大模型微调与对齐

这一章用于回答“模型已经预训练好了，怎么让它更适合具体任务、更听指令、更安全”。重点是 SFT、RLHF、DPO、LoRA、QLoRA，以及微调和 RAG 怎么选。


### SFT 指令微调

SFT，即 Supervised Fine-Tuning，监督式指令微调。它用高质量的“指令-回答”数据继续训练模型，让模型学会按照用户指令完成任务。

预训练模型更像“会续写文本”，SFT 让模型更像“会听指令的助手”。

常见数据形态：

```json
{
  "messages": [
    {"role": "system", "content": "你是一个专业的合同审核助手。"},
    {"role": "user", "content": "请提取合同中的甲方、乙方和金额。"},
    {"role": "assistant", "content": "{\"甲方\": \"A公司\", \"乙方\": \"B公司\", \"金额\": \"100万元\"}"}
  ]
}
```

工程上常见用途：

- 让模型稳定输出 JSON。
- 学会企业内部话术。
- 适配特定抽取、分类、总结任务。
- 提高多轮对话任务的一致性。
- 修正模型在某类任务上的常见错误。

关键点：

- 数据质量比数据数量更重要。
- 训练格式要和推理 chat template 一致。
- 输出格式要统一，否则模型会学乱。
- 不要把测试集样本混进训练集。
- SFT 后必须做回归评估，防止通用能力下降。

面试答法：

> SFT 是用人工或业务构造的高质量指令数据继续训练模型，让模型更会按指令完成任务。工程上常用于稳定格式、适配业务话术和垂直任务，但核心难点在数据质量、格式一致性和评估。

### 对齐训练 Alignment

对齐的目标是让模型输出更符合人类偏好、安全规范和实际使用需求。

常见方法：

- RLHF：基于人类反馈的强化学习。
- DPO：Direct Preference Optimization，直接用偏好对优化。
- RLAIF：用 AI 反馈辅助对齐。

面试答法：

> SFT 让模型会回答，对齐训练让模型回答得更符合人类偏好，比如更有帮助、更安全、更少有害内容。


### RLHF

RLHF，即 Reinforcement Learning from Human Feedback，基于人类反馈的强化学习。

它解决的问题：

> 模型的预训练目标是预测下一个 token，但人类真正想要的是有帮助、真实、安全、符合偏好的回答。RLHF 用人类偏好来调整模型行为。

典型流程：

1. 用同一个 prompt 生成多个回答。
2. 人类标注哪个回答更好。
3. 用偏好数据训练 Reward Model。
4. 用 PPO 等强化学习方法优化模型，让模型生成更高 reward 的回答。

工程关注：

- 人类偏好标注成本高。
- Reward Model 本身可能有偏差。
- 强化学习训练不稳定。
- 如果 reward 设计不好，模型可能 reward hacking。
- 生产团队通常不会从零做 RLHF，更多使用已有对齐模型。

面试答法：

> RLHF 的核心是把人类偏好转成 reward 信号，再优化模型生成更符合人类偏好的回答。它能提升帮助性和安全性，但工程成本高、训练复杂。


### DPO

DPO，即 Direct Preference Optimization，直接偏好优化。

它和 RLHF 的区别：

- RLHF 通常需要训练 Reward Model，再做强化学习。
- DPO 直接用 chosen / rejected 偏好对训练模型。
- 流程更简单，训练更稳定，工程实现成本更低。

偏好数据形式：

```json
{
  "prompt": "解释什么是 RAG",
  "chosen": "RAG 是检索增强生成...",
  "rejected": "RAG 是一种数据库..."
}
```

工程用途：

- 让模型更偏好高质量回答。
- 减少啰嗦、幻觉或格式错误。
- 对齐业务偏好，比如更简洁、更正式、更安全。

面试答法：

> DPO 可以理解为更轻量的偏好对齐方法，它不显式训练 reward model，而是直接让模型提高 chosen answer 的概率、降低 rejected answer 的概率。

### Fine-tuning 和 RAG 怎么选

RAG 适合：

- 知识更新频繁。
- 需要引用来源。
- 企业私有知识问答。
- 不希望重新训练模型。

微调适合：

- 固定输出格式。
- 特定任务模式。
- 风格和语气适配。
- 领域术语和标注规范。

面试答法：

> 如果问题是模型缺少外部知识，优先 RAG；如果问题是模型不会按特定格式、风格或任务习惯输出，可以考虑微调。

### 全量微调

全量微调会更新模型所有参数。

优点：

- 适配能力强。

缺点：

- 显存和算力成本高。
- 容易灾难性遗忘。
- 多任务维护成本高。

面试答法：

> 全量微调效果可能更强，但成本很高，普通业务场景更多会考虑 LoRA 这类参数高效微调。

### PEFT

PEFT，即 Parameter-Efficient Fine-Tuning，参数高效微调。

目标：

- 冻结大部分原模型参数。
- 只训练少量新增或低秩参数。
- 降低显存和训练成本。

常见方法：

- LoRA
- Prefix Tuning
- Prompt Tuning
- Adapter


### LoRA

LoRA，即 Low-Rank Adaptation，是工程上最常用的参数高效微调方法之一。

核心思想：

> 冻结原模型权重，只训练少量低秩矩阵，让模型学习一个任务相关的增量。

直观公式：

```text
W' = W + BA
```

其中：

- `W` 是原模型权重，冻结不训练。
- `A` 和 `B` 是新增的低秩矩阵，需要训练。
- `BA` 是对原权重的低秩更新。

为什么省显存：

- 不训练全部参数。
- 只保存 LoRA 小矩阵的梯度和优化器状态。
- 可以用较小 GPU 完成垂直任务适配。

常见超参数：

- `r`：rank，越大表达能力越强，但参数更多。
- `lora_alpha`：缩放系数。
- `lora_dropout`：防止过拟合。
- `target_modules`：把 LoRA 加到哪些层。

工程优点：

- 训练成本低。
- 多任务可以保存多个 adapter。
- 可以快速切换业务版本。
- 可以选择 merge 到 base model。

工程风险：

- base model 版本和 adapter 不匹配会出问题。
- rank 太小可能学不动，太大可能过拟合。
- 数据格式不好时，LoRA 也会学坏。

面试答法：

> LoRA 不更新大模型主体参数，而是训练少量低秩增量参数。它适合低成本做领域适配、格式适配和业务话术适配，是工程里非常常用的微调方案。


### QLoRA

QLoRA 是 Quantized LoRA，可以理解为“量化基座模型 + LoRA 微调”。

核心做法：

- 基础模型用 4-bit 等低精度加载，减少显存。
- 原模型权重冻结。
- 只训练 LoRA adapter。
- 反向传播时通过量化权重参与计算。

为什么有用：

> 它显著降低了微调大模型的显存门槛，让单卡或较小资源也能做较大模型的 LoRA 微调。

常见概念：

- 4-bit quantization。
- NF4。
- double quantization。
- paged optimizer。

工程注意：

- 训练速度可能受实现影响。
- 量化会带来一定精度损失。
- 仍然需要高质量数据和评估。
- 部署时要确认推理框架是否支持对应量化格式。

面试答法：

> QLoRA 通过 4-bit 量化加载基座模型，只训练 LoRA 参数，大幅降低显存占用。它解决的是训练资源门槛问题，不解决数据质量问题。

### 微调数据怎么准备

高质量数据比数量更重要。

建议：

- 指令清晰。
- 输出格式一致。
- 覆盖真实业务场景。
- 包含困难样本和边界样本。
- 去掉错误答案和冲突标注。
- 训练集、验证集、测试集分开。

常见格式：

```json
{
  "instruction": "从文本中抽取公司名称和金额",
  "input": "A 公司向 B 公司支付 100 万元。",
  "output": "{\"payer\":\"A 公司\",\"payee\":\"B 公司\",\"amount\":\"100 万元\"}"
}
```

### 微调常见风险

- 过拟合：训练集表现好，泛化差。
- 灾难性遗忘：原有能力下降。
- 数据污染：测试题进入训练集。
- 格式学坏：输出不稳定。
- 安全能力下降。

解决方式：

- 使用验证集。
- 控制学习率和训练步数。
- 混入通用指令数据。
- 做回归评估。
- 保留模型版本和数据版本。

### 微调数据格式 Chat Template

工程上微调对话模型时，不能只把问题和答案简单拼起来，通常要使用模型对应的 chat template。

常见字段：

```json
[
  {"role": "system", "content": "你是一个专业客服助手。"},
  {"role": "user", "content": "怎么申请退款？"},
  {"role": "assistant", "content": "你可以在订单详情页点击申请退款。"}
]
```

为什么重要：

- 不同模型的 system、user、assistant 标记不同。
- 模型训练时见过特定格式，推理也应该保持一致。
- 格式错了，模型可能学不到真正的对话边界。

面试答法：

> 微调数据必须和模型的 chat template 对齐。训练格式和推理格式不一致，会导致模型上线后表现不稳定。

### Instruction Tuning 数据质量

高质量样本通常满足：

- 指令明确。
- 答案正确。
- 输出格式稳定。
- 覆盖真实业务问题。
- 包含边界情况。
- 没有互相冲突的标注。
- 不泄露隐私数据。

面试答法：

> 微调不是数据越多越好，低质量数据会把模型教坏。工程上经常先做数据清洗和人工抽检，再训练。

### 微调数据配比

如果只用某个垂直任务数据微调，模型可能在其他能力上退化。

常见策略：

- 业务数据 + 通用指令数据混合。
- 简单样本 + 困难样本混合。
- 正常样本 + 边界样本混合。
- 多轮对话样本 + 单轮任务样本混合。

面试答法：

> 数据配比会影响模型行为。只喂单一格式或单一任务，模型可能过拟合这个模式，泛化和通用能力下降。

### 训练集切分

常见切分：

```text
train：训练参数
valid：调超参数、早停、选 checkpoint
test：最终报告效果
```

注意：

- 同一个用户、同一个文档来源的相似样本不要同时出现在 train 和 test。
- 测试集不能参与调参。
- 对 RAG/问答任务，要防止答案文本泄漏到训练样本里。

### 微调训练参数

常见参数：

- learning rate
- batch size
- gradient accumulation steps
- epoch
- max sequence length
- warmup ratio
- weight decay
- LoRA rank `r`
- LoRA alpha
- LoRA dropout
- target modules

面试答法：

> LoRA 微调里常调的不是全部模型参数，而是 LoRA rank、学习率、训练轮数、目标层和数据质量。rank 越大表达能力越强，但显存和过拟合风险也会增加。

### Gradient Accumulation

梯度累积用于在显存不够时模拟更大的 batch size。

例子：

```text
micro batch size = 2
gradient accumulation steps = 8
effective batch size = 16
```

面试答法：

> 显存放不下大 batch 时，可以多次 forward/backward 后再更新一次参数，这就是梯度累积。

### Gradient Checkpointing

Gradient Checkpointing 用计算换显存。

普通训练：

- 保存大量中间激活。
- 反向传播时直接使用。

Checkpointing：

- 只保存部分激活。
- 反向传播时重新计算缺失激活。

面试答法：

> Gradient checkpointing 可以显著降低训练显存，但会增加计算时间。微调大模型时很常用。

### LoRA Target Modules

LoRA 通常加在 Transformer 的线性层上。

常见 target modules：

```text
q_proj
k_proj
v_proj
o_proj
gate_proj
up_proj
down_proj
```

经验：

- 只训 attention 层更省资源。
- attention + MLP 层表达能力更强。
- target modules 越多，训练参数越多。

面试答法：

> LoRA 不是随便插层。常见做法是对 attention 的 q/v 或 q/k/v/o 加 LoRA，也可以加到 MLP 投影层以增强适配能力。

### LoRA 合并与部署

LoRA 训练后有两种部署方式：

1. Base model + LoRA adapter 分开加载。
2. Merge LoRA，把 adapter 权重合并进 base model。

分开加载：

- 多任务切换方便。
- 一个 base 可挂多个 adapter。

合并部署：

- 推理链路简单。
- 可能更利于某些部署框架优化。

面试答法：

> 如果同一个基础模型要支持多个业务 adapter，可以分开加载；如果只部署一个固定任务，可以考虑 merge 后部署。

### 微调框架

常见工具：

- Hugging Face Transformers
- PEFT
- TRL
- DeepSpeed
- Accelerate
- LLaMA-Factory
- Axolotl

面试答法：

> 工程上不会从零写训练循环，通常用 Transformers + PEFT 做 LoRA，用 DeepSpeed 或 Accelerate 处理多卡和显存优化。

### Checkpoint

Checkpoint 是训练过程中保存的模型状态。

包含：

- 模型参数或 adapter 参数。
- optimizer 状态。
- scheduler 状态。
- 当前 step。

用途：

- 训练中断后恢复。
- 选择验证集表现最好的版本。
- 对比不同训练阶段效果。

### 微调评估

微调后不能只看 loss。

需要评估：

- 任务准确率。
- 格式遵守率。
- 幻觉率。
- 安全性。
- 通用能力是否退化。
- 人工抽检。
- 和 prompt/RAG baseline 对比。

面试答法：

> Loss 下降不代表业务效果一定提升。微调必须结合离线评估集、人工评估和线上灰度反馈。

### Catastrophic Forgetting

灾难性遗忘指模型微调后忘掉原来的通用能力。

表现：

- 原本能回答的问题答不好。
- 安全拒答能力下降。
- 输出风格变得单一。

缓解：

- 降低学习率。
- 减少训练 epoch。
- 混入通用数据。
- 使用 LoRA 而不是全量微调。
- 做回归评估。

### 微调上线流程

推荐流程：

```text
确定任务 -> 准备数据 -> 训练 LoRA -> 离线评估 -> 人工抽检 -> 灰度上线 -> 监控反馈 -> 迭代数据
```

上线前 checklist：

- 模型版本。
- 数据版本。
- prompt 版本。
- adapter 版本。
- 评估报告。
- 回滚方案。

### 微调常见工程坑

- 数据格式和推理 chat template 不一致。
- 训练数据太少但 epoch 太多，过拟合。
- 学习率太大，模型输出变差。
- max length 太短，样本被截断。
- 没有验证集，只看训练 loss。
- adapter 和 base model 版本不匹配。
- 推理时忘记加载 LoRA adapter。
- 微调后没有做安全评估。

面试答法：

> 微调工程里最常见的问题不是算法不会，而是数据格式、版本管理、评估和部署链路不严谨。


## 7. 大模型推理与部署

这一章用于回答“模型上线后是怎么生成答案的，以及怎么优化延迟和成本”。重点是自回归生成、prefill、decode、KV cache、量化、batching 和部署方式。


### 推理 Inference

推理就是模型参数固定后，根据输入 prompt 生成输出的过程。

LLM 推理通常是自回归生成：

```text
输入 prompt -> 生成第 1 个 token
输入 prompt + 第 1 个 token -> 生成第 2 个 token
不断重复直到结束
```

工程特点：

- 输出越长，生成越慢。
- 输入越长，首 token 越慢。
- 推理不需要梯度，但需要大量显存放模型权重和 KV cache。
- Chat 产品通常使用流式输出降低用户等待感。

和普通深度学习推理的区别：

- 图像分类通常一次 forward 得到结果。
- LLM 是逐 token 多次 forward。
- 因此 LLM 更关注 TTFT、tokens/s、KV cache 和 batching。

面试答法：

> LLM 推理是逐 token 自回归生成。输入长度主要影响 prefill，输出长度主要影响 decode，所以优化延迟要分别看输入和输出。


### Prefill 和 Decode

LLM 推理通常分成两个阶段：prefill 和 decode。

Prefill：

- 处理完整输入 prompt。
- 一次性计算输入 tokens 的隐藏状态。
- 建立 KV cache。
- 输入越长，prefill 越慢。
- 主要影响 TTFT，也就是首 token 延迟。

Decode：

- 每次生成一个新 token。
- 使用已有 KV cache。
- 输出越长，decode 越久。
- 主要影响每 token 延迟和总生成时间。

工程例子：

```text
用户输入 10k tokens 的长文档：
prefill 很慢，首 token 延迟高。

用户让模型写 2000 字文章：
decode 很久，总生成时间高。
```

优化方向：

- 缩短 prompt。
- 减少无关 RAG chunk。
- 限制最大输出 token。
- 使用流式输出降低感知延迟。
- 用更快推理框架提升 decode tokens/s。

面试答法：

> Prefill 处理输入上下文，decode 逐 token 生成输出。长输入拖慢 prefill，长输出拖慢 decode。


### KV Cache

KV cache 缓存历史 token 在 attention 中的 Key 和 Value，避免每生成一个 token 都重新计算完整历史。

为什么需要：

> 自回归生成时，第 t 个 token 需要关注前面所有 token。如果不缓存，每一步都要重复算历史 token 的 K/V，成本非常高。

优点：

- 大幅加速 decode。
- 让长文本生成变得可接受。

代价：

- 占用显存。
- batch 越大，占用越高。
- 上下文越长，占用越高。
- 层数和 hidden size 越大，占用越高。

工程影响：

- 长上下文会降低并发。
- 多轮对话历史不能无限塞。
- RAG top-k 太大也会增加 KV cache。
- Serving 框架需要高效管理 KV cache。

相关工程概念：

- PagedAttention。
- KV cache eviction。
- prefix cache。
- context length limit。

面试答法：

> KV cache 是 LLM 推理加速的关键，它用显存换速度。工程上长上下文和高并发的主要压力之一就是 KV cache 显存。


### Decoding 策略

Decoding 策略决定模型如何从下一个 token 的概率分布中选 token。

Greedy Decoding：

- 每次选概率最高的 token。
- 稳定、确定。
- 容易重复或不够有创造性。

Beam Search：

- 保留多个候选序列。
- 适合机器翻译等目标明确任务。
- 对开放式聊天不一定好，可能输出僵硬。

Sampling：

- 按概率采样。
- 输出更多样。
- 适合创意写作、开放式问答。

Top-k：

- 只从概率最高的 k 个 token 里采样。

Top-p：

- 从累计概率达到 p 的候选集合中采样。
- 比 top-k 更动态。

Temperature：

- 调整概率分布尖锐程度。
- 低 temperature 更稳定。
- 高 temperature 更多样但更容易跑偏。

工程建议：

- 代码生成、JSON 输出：低 temperature。
- 客服问答：低到中等 temperature。
- 创意生成：较高 temperature。
- 生产环境要固定参数，并记录版本。

面试答法：

> 解码策略影响稳定性和多样性。结构化任务通常降低随机性，开放创作任务可以提高随机性。


### 推理性能指标

LLM 推理不能只看“总耗时”，要拆成多个指标。

TTFT，Time To First Token：

- 首 token 延迟。
- 用户多久能看到第一个字。
- Chat 产品非常关注。

TPOT，Time Per Output Token：

- 每生成一个 token 的平均时间。
- 反映 decode 速度。

Throughput：

- 吞吐量。
- 常见单位：tokens/s、requests/s。

Latency：

- 总延迟。
- 从请求开始到完整回答结束。

Queue Waiting Time：

- 请求在队列里等待 GPU 的时间。
- 高并发时很关键。

GPU 指标：

- GPU utilization。
- GPU memory usage。
- KV cache usage。

工程解读：

- TTFT 高：可能输入太长、prefill 慢、排队久。
- TPOT 高：decode 慢、batch 太大、模型太大。
- 吞吐低：GPU 利用率低、batching 不好。
- OOM：模型权重或 KV cache 太大。

面试答法：

> Chat 场景重点看 TTFT 和流式体验，批处理场景更关注吞吐。线上排查还要看队列等待、GPU 利用率和 KV cache 占用。


### 推理优化

推理优化的目标通常有三个：降低延迟、提高吞吐、降低成本。

从输入侧优化：

- 缩短 system prompt。
- 压缩历史对话。
- RAG 只放必要 chunk。
- 对长文档先摘要再问答。
- 限制最大输入 token。

从输出侧优化：

- 限制 `max_tokens`。
- 对结构化任务要求简短输出。
- 使用 stop sequence。
- 流式输出降低感知延迟。

从模型侧优化：

- 使用更小模型。
- 使用量化模型。
- 蒸馏小模型。
- 简单任务走小模型，复杂任务走大模型。

从 serving 侧优化：

- KV cache。
- continuous batching。
- PagedAttention。
- tensor parallel。
- 多副本部署。
- 缓存高频结果。

工程权衡：

- batch 大吞吐高，但单请求延迟可能上升。
- 量化省显存，但可能损失效果。
- 小模型快且便宜，但复杂任务能力不足。
- 长上下文方便，但 prefill 慢、KV cache 贵。

面试答法：

> 推理优化要分层看：prompt 长度、输出长度、模型大小、量化、batching、KV cache、缓存和模型路由。不同业务要在质量、延迟和成本之间权衡。


### Continuous Batching

Continuous batching 是 LLM serving 中非常常见的吞吐优化技术。

普通 batching：

- 等一批请求凑齐。
- 一起推理。
- 这一批里如果有长输出，请求可能互相拖累。

Continuous batching：

- 请求可以动态加入正在运行的 batch。
- 已完成的请求可以及时退出。
- 新请求不用等整批全部结束。

为什么适合 LLM：

- 不同用户输出长度差异很大。
- 有些请求只生成几十 token，有些生成上千 token。
- 动态调度能提高 GPU 利用率。

工程指标：

- batch size。
- queue waiting time。
- TTFT。
- tokens/s。
- GPU utilization。

面试答法：

> Continuous batching 解决的是 LLM 请求输出长度不一致的问题，让请求动态进出 batch，提高 GPU 利用率和整体吞吐。

### 量化 Quantization

量化是用更低 bit 表示模型权重或激活，从而降低显存、减少带宽压力，并可能提升推理速度。

常见精度：

- FP32：精度高，显存大。
- FP16 / BF16：常见推理和训练精度。
- INT8：推理量化常见。
- INT4：更省显存，但质量风险更高。

常见方法：

- PTQ：Post-Training Quantization，训练后量化。
- QAT：Quantization-Aware Training，量化感知训练。
- GPTQ：常见权重量化方法。
- AWQ：Activation-aware Weight Quantization。

工程收益：

- 降低显存占用。
- 单卡能放下更大模型。
- 提高吞吐。
- 降低部署成本。

工程风险：

- 数学、代码、复杂推理能力可能下降。
- 长上下文稳定性可能变化。
- 不同硬件和推理框架支持不同。
- 量化格式和 serving 框架要匹配。

评估方式：

- 用业务评估集对比量化前后。
- 看准确率、格式遵守率、幻觉率。
- 看 TTFT、tokens/s、显存占用。

面试答法：

> 量化是推理部署常用优化，用一定精度损失换显存和速度。工程上不能只看能否运行，还要评估质量、延迟和框架兼容性。


### 蒸馏 Distillation

蒸馏是用强模型 teacher 指导小模型 student，让小模型学习大模型的行为。

为什么需要蒸馏：

- 大模型效果好但成本高、延迟高。
- 某些业务任务范围固定，不一定需要大模型。
- 希望把大模型能力压缩到小模型里部署。

常见做法：

1. 用 teacher model 生成高质量答案。
2. 构造 prompt-answer 训练数据。
3. 用这些数据 SFT 小模型。
4. 用真实业务评估集验证 student 效果。

蒸馏数据来源：

- 大模型生成答案。
- 大模型生成思路或解释。
- 大模型对已有答案打分和改写。
- 人工审核后的 teacher 输出。

工程场景：

- 用大模型生成标注数据，训练小分类器。
- 用 GPT 级模型生成客服问答，蒸馏到本地小模型。
- 用大模型生成结构化抽取样本，训练小模型做固定抽取。
- 用强 reranker 产生排序标签，训练轻量 reranker。

优点：

- 降低推理成本。
- 降低延迟。
- 方便私有化部署。
- 对固定任务很有效。

缺点：

- student 上限受模型容量限制。
- teacher 的错误可能被 student 学到。
- 对开放复杂推理任务，蒸馏效果不一定稳定。
- 蒸馏数据分布如果太窄，泛化会差。

和微调的关系：

> 蒸馏通常会落到一次微调过程。区别是训练数据很多来自 teacher model，而不是纯人工标注。

和 RAG 的关系：

> 如果问题是知识更新，RAG 更合适；如果问题是固定任务降本提速，蒸馏更合适。

面试答法：

> 蒸馏就是让小模型模仿大模型。工程上常用于降本和加速，比如用大模型生成高质量训练数据，再微调小模型处理固定场景任务。


### Speculative Decoding

Speculative Decoding，投机解码，是一种推理加速方法。

核心思想：

> 让小模型先快速猜一段 token，再让大模型一次性验证。如果猜对，就接受多个 token；如果猜错，只回退一部分。

参与模型：

- Draft model：小模型，负责快速生成候选。
- Target model：大模型，负责验证候选。

为什么能加速：

- 大模型逐 token decode 很贵。
- 如果小模型猜得比较准，大模型可以一次验证多个 token。
- 减少大模型调用步数。

适用条件：

- 小模型和大模型输出分布接近。
- 任务不是极端复杂。
- 系统能承受两个模型同时部署。

工程注意：

- 实现复杂度更高。
- 需要额外小模型资源。
- 加速效果依赖 draft model 命中率。

面试答法：

> 投机解码是用小模型先猜、大模型验证。猜得准时可以减少大模型逐 token 生成次数，从而提升推理速度。


### 部署方式

LLM 部署方式大致分成 API 调用和私有化部署。

API 调用：

- 使用第三方模型服务。
- 上手快。
- 不需要维护 GPU。
- 按 token 付费。
- 数据要发送到外部服务。

适合：

- 早期 Demo。
- 快速验证业务价值。
- 团队没有 GPU 运维能力。

私有化部署：

- 模型部署在自有服务器、私有云或本地机房。
- 数据控制力更强。
- 可做深度优化。
- 需要 GPU、推理框架、监控和运维。

适合：

- 数据敏感。
- 调用量大，API 成本高。
- 延迟要求稳定。
- 需要定制模型或 adapter。

混合架构：

- 默认用私有模型处理常规请求。
- 复杂请求 fallback 到云端强模型。
- 或者用云端模型做评估、标注和蒸馏。

常见推理框架：

- vLLM：高吞吐 serving，PagedAttention。
- TGI：Hugging Face 生态。
- TensorRT-LLM：NVIDIA GPU 高性能优化。
- llama.cpp：本地和边缘设备友好。

面试答法：

> 早期通常先用 API 快速验证，规模上来或数据敏感后再考虑私有化部署。私有化不是只把模型跑起来，还要解决 serving、监控、限流、灰度和回滚。


### 模型选型

模型选型不是越大越好，而是看任务、成本、延迟和稳定性。

考虑维度：

- 任务类型：问答、总结、抽取、代码、数学、Agent。
- 中文能力。
- 上下文长度。
- 工具调用能力。
- 结构化输出稳定性。
- 推理速度。
- token 成本。
- 私有化部署难度。
- 安全和合规要求。
- 社区生态和框架支持。

常见策略：

- 简单分类/抽取：小模型或传统 ML。
- 普通知识问答：中等模型 + RAG。
- 复杂推理/Agent：强模型。
- 长文档：长上下文模型 + RAG 压缩。
- 代码任务：代码能力强的模型。

工程上常做模型路由：

```text
低风险简单请求 -> 小模型
复杂请求 -> 大模型
大模型失败 -> fallback 模型
高价值用户 -> 更强模型
低优先级批处理 -> 便宜模型
```

评估方式：

- 建业务评估集。
- 比较准确率、格式错误率、幻觉率。
- 比较 TTFT、总延迟、成本。
- 做人工抽检。
- 小流量灰度。

面试答法：

> 模型选型要用评估集说话。不能只看榜单，要结合业务数据比较质量、延迟、成本、上下文、工具调用和部署复杂度。

### 训练和推理的区别

训练：

- 输入样本，计算 loss。
- 反向传播更新参数。
- 需要保存梯度和优化器状态。
- 显存和算力需求高。

推理：

- 参数固定。
- 只做前向计算生成结果。
- 不需要梯度。
- 更关注延迟、吞吐和成本。

面试答法：

> 训练是让模型变好，推理是使用模型。训练要反向传播更新参数，推理只前向生成，所以推理显存压力小一些，但长上下文下 KV cache 也会很占显存。

### 微调和提示词工程的区别

Prompt Engineering：

- 不改模型参数。
- 调整输入提示。
- 成本低，迭代快。

Fine-tuning：

- 改变模型参数或 adapter 参数。
- 成本更高。
- 适合稳定任务和固定格式。

面试答法：

> 能用 prompt 和 RAG 解决的先不用微调。微调适合需求稳定、数据质量高、prompt 很难稳定约束的场景。

### 常见面试开放题：如何微调一个领域模型

答题框架：

1. 明确任务和评估指标。
2. 收集真实业务数据。
3. 清洗、去重、脱敏。
4. 构造 instruction-output 数据。
5. 划分 train/valid/test。
6. 选择基座模型。
7. 选择 LoRA/QLoRA 或全量微调。
8. 训练并观察 loss 和验证集指标。
9. 做人工评估和安全评估。
10. 灰度上线，监控质量、延迟和成本。

### 常见面试开放题：怎么优化 LLM 推理延迟

答题框架：

- 缩短输入 prompt。
- 控制输出 token。
- 开启流式输出降低感知延迟。
- 用更小或更快的模型。
- 使用 KV cache。
- 使用 continuous batching。
- 使用量化。
- 缓存高频请求。
- RAG 减少无关 chunk。
- 并行工具调用。

### 常见面试开放题：模型效果不好怎么办

答题框架：

1. 判断是检索问题、prompt 问题、模型能力问题还是数据问题。
2. 如果缺知识，优先优化 RAG。
3. 如果格式不稳，优化 prompt 或结构化输出。
4. 如果任务模式固定，可考虑 SFT/LoRA。
5. 建评估集做对比，不凭感觉改。

### 推理服务 Serving

推理服务是把模型封装成可被业务调用的服务。

常见形态：

```text
Client -> API Gateway -> Model Gateway -> Inference Server -> GPU Model
```

工程关注：

- 并发请求。
- 流式输出。
- 超时控制。
- 模型版本。
- 权限和限流。
- 日志和监控。
- 故障降级。

面试答法：

> 推理部署不是简单把模型 load 起来，还要处理 API、并发、流式、限流、监控、版本和回滚。

### Model Gateway

Model Gateway 是模型调用网关，统一封装不同模型供应商或不同本地模型。

作用：

- 统一 API。
- 隐藏不同模型接口差异。
- 做模型路由。
- 做 fallback。
- 统计 token 和成本。
- 做限流和鉴权。

面试答法：

> Model Gateway 能把业务和具体模型解耦。换模型、做 A/B test、降级和统计成本时会更方便。

### 模型路由

模型路由是根据请求类型选择不同模型。

例子：

- 简单分类 -> 小模型。
- 复杂推理 -> 大模型。
- 长文档 -> 长上下文模型。
- 代码任务 -> 代码能力强的模型。
- 低优先级请求 -> 便宜模型。

好处：

- 降低成本。
- 降低延迟。
- 提高稳定性。

### Fallback 降级

模型调用失败时，需要 fallback。

常见策略：

- 大模型失败 -> 小模型。
- 主供应商失败 -> 备用供应商。
- RAG 失败 -> 返回“暂时无法回答”并给错误原因。
- 工具超时 -> 跳过工具并说明限制。

面试答法：

> 生产环境不能假设模型 API 永远可用，要有超时、重试、降级和用户可理解的错误信息。

### 推理并发

LLM 服务的并发瓶颈通常在：

- GPU 显存。
- KV cache。
- prefill 计算。
- decode token 生成速度。
- 上游 API rate limit。

常见控制：

- 最大并发请求数。
- 最大 batch size。
- 最大输入 token。
- 最大输出 token。
- 队列长度。
- 用户级限额。

### Dynamic Batching

Dynamic batching 会把短时间内到达的多个请求合成 batch，提高 GPU 利用率。

权衡：

- batch 大，吞吐高。
- 等 batch 会增加单请求延迟。

面试答法：

> Batching 是吞吐和延迟的权衡。在线聊天更关注首 token 延迟，离线批处理更关注总吞吐。

### Continuous Batching 的工程意义

LLM 请求输出长度不同。如果普通 batch 中某个请求很长，其他请求可能被拖住。

Continuous batching 的优势：

- 生成过程中动态加入新请求。
- 已完成请求及时退出 batch。
- GPU 利用率更高。

常见框架：

- vLLM
- TGI

### PagedAttention

PagedAttention 是 vLLM 中用于高效管理 KV cache 的机制。

直观理解：

> 类似操作系统分页，把 KV cache 切成块管理，减少显存碎片，提高 batch 和并发能力。

面试答法：

> vLLM 的 PagedAttention 主要优化 KV cache 管理，让长上下文和高并发推理时显存利用更高效。

### KV Cache 显存估算

KV cache 占用和这些因素相关：

- batch size
- sequence length
- hidden size
- layer 数
- attention head 数
- 数据类型，如 FP16/BF16/INT8

直观结论：

> batch 越大、上下文越长、模型层数越多，KV cache 占用越高。

工程影响：

- 长上下文会显著降低并发。
- 限制 max context length 能保护服务稳定性。
- 多轮对话需要摘要或裁剪历史。

### Context Length 管理

上下文太长的问题：

- prefill 慢。
- KV cache 大。
- 成本高。
- 无关信息干扰模型。

常见策略：

- 截断历史。
- 对历史对话做摘要。
- RAG 只取 top-k 相关片段。
- 对长文档先分段处理。
- 限制用户输入长度。

### 流式输出 Streaming

LLM 通常逐 token 生成，流式输出可以降低用户感知延迟。

后端流程：

```text
请求模型流 -> 接收 token chunk -> 通过 SSE/WebSocket 推给前端 -> 结束时写入完整消息
```

注意：

- 用户取消时要中断上游请求。
- 断连时要清理资源。
- 日志里要记录完整输出或 partial output。
- 前端要处理 Markdown 未闭合。

### 请求取消 Cancel

用户点击停止生成时，后端应尽量取消：

- HTTP 连接。
- 上游模型请求。
- 工具调用。
- 后台任务。

为什么重要：

- 节省 token 成本。
- 释放 GPU/连接资源。
- 提升用户体验。

### 限流 Rate Limit

为什么要限流：

- 防止刷接口。
- 控制成本。
- 保护 GPU 服务。
- 避免上游模型 API 429。

维度：

- user id。
- API key。
- IP。
- tenant。
- model。
- endpoint。

常见算法：

- 固定窗口。
- 滑动窗口。
- 令牌桶。
- 漏桶。

### 超时 Timeout

推理请求要设置多层超时：

- API Gateway 超时。
- 后端 handler 超时。
- 模型请求超时。
- 工具调用超时。
- SSE 空闲超时。

面试答法：

> 没有 timeout 的模型调用很危险，可能导致连接和 worker 被长期占用，最终拖垮服务。

### 重试 Retry

适合重试：

- 网络抖动。
- 429。
- 502/503/504。
- 临时上游错误。

不适合盲目重试：

- 非幂等工具调用。
- 已经产生副作用的请求。
- 长文本生成到一半。

策略：

- 最大重试次数。
- 指数退避。
- jitter 随机抖动。
- 记录 request id 防重复。

### 推理缓存

可缓存：

- embedding。
- 检索结果。
- rerank 结果。
- 高频 prompt 的回答。
- 系统 prompt 编译结果。

谨慎缓存：

- 用户私有数据。
- 带权限的 RAG 结果。
- 强个性化回答。

面试答法：

> 缓存可以降成本和延迟，但 LLM 应用必须考虑权限、prompt 版本、模型版本和用户上下文。

### 量化部署

常见量化：

- FP16 / BF16。
- INT8。
- INT4。
- GPTQ。
- AWQ。

工程关注：

- 量化后质量是否下降。
- 推理框架是否支持。
- GPU 是否支持对应 kernel。
- 长上下文和工具调用任务是否受影响。

面试答法：

> 量化不是只看模型能不能跑起来，还要用评估集确认质量、格式遵守和推理能力是否还能接受。

### 多 GPU 推理

什么时候需要多 GPU：

- 单卡放不下模型。
- 单卡吞吐不够。
- 长上下文 KV cache 压力大。

常见方式：

- Tensor parallel。
- Pipeline parallel。
- 多副本部署。

面试答法：

> 如果模型单卡能放下，常用多副本提升并发；如果单卡放不下，才需要张量并行或流水线并行切模型。

### CPU Offload

CPU offload 把部分权重或计算放到 CPU 内存。

优点：

- 降低 GPU 显存压力。

缺点：

- PCIe 传输慢。
- 延迟变高。

适合：

- 本地低成本实验。
- 对延迟不敏感的场景。

### 推理框架选型

vLLM：

- 高吞吐。
- PagedAttention。
- OpenAI-compatible server。

TGI：

- Hugging Face 生态。
- 生产 serving 能力较完整。

TensorRT-LLM：

- NVIDIA 优化。
- 性能强。
- 工程配置复杂。

llama.cpp：

- CPU/边缘设备友好。
- 适合本地轻量部署。

面试答法：

> 如果要快速搭建高吞吐 LLM 服务，vLLM 是常见选择；如果追求 NVIDIA GPU 极致性能，可以考虑 TensorRT-LLM。

### OpenAI-Compatible API

很多本地推理服务会兼容 OpenAI API 格式。

好处：

- 前后端代码少改。
- 可以复用 SDK。
- 方便在云模型和本地模型之间切换。

常见接口：

```text
/v1/chat/completions
/v1/completions
/v1/embeddings
```

### 模型版本管理

需要记录：

- base model。
- adapter version。
- quantization version。
- prompt version。
- tokenizer version。
- serving config。

为什么：

- 方便复现问题。
- 支持回滚。
- 支持 A/B test。

### 推理监控

关键指标：

- QPS。
- 并发数。
- TTFT。
- 每 token 延迟。
- 总延迟。
- tokens/s。
- input tokens。
- output tokens。
- GPU 显存。
- GPU 利用率。
- queue waiting time。
- error rate。
- 429/5xx 数量。

面试答法：

> LLM 服务监控不能只看 QPS，还要看 token 维度、首 token 延迟、队列等待时间和 GPU 利用率。

### 成本统计

需要按维度统计：

- 用户。
- tenant。
- 模型。
- 应用。
- input tokens。
- output tokens。
- tool calls。
- embedding calls。

用途：

- 预算控制。
- 计费。
- 发现异常调用。
- 优化模型路由。

### 灰度发布

灰度方式：

- 按用户比例。
- 按 tenant。
- 按接口。
- 按模型版本。

上线流程：

```text
离线评估 -> 小流量灰度 -> 指标观察 -> 扩大流量 -> 全量
```

回滚条件：

- 错误率升高。
- 延迟升高。
- 用户负反馈升高。
- 成本异常。

### 推理服务常见工程坑

- 没有限制 max_tokens，成本失控。
- 上下文太长导致 TTFT 很高。
- 没有流式输出，用户等待感强。
- 没有取消机制，用户停止后还在烧 token。
- 没有 request id，排查问题困难。
- 没有版本记录，效果变化无法复现。
- RAG chunk 太多，prompt 又贵又慢。
- 只看请求数，不看 token 数。
- GPU 服务没有队列和限流，被突发流量打崩。

### 面试开放题：如何设计一个 LLM 推理服务

答题框架：

1. API 层接收请求，做鉴权和限流。
2. Model Gateway 做模型路由和 fallback。
3. 推理服务用 vLLM/TGI 部署模型。
4. 支持 SSE 流式输出。
5. 设置 max input/output tokens。
6. 做 timeout、retry、cancel。
7. 记录 token、延迟、错误、模型版本。
8. 监控 GPU、队列、TTFT、吞吐。
9. 支持灰度和回滚。

### 面试开放题：如何提升吞吐同时不明显伤害延迟

答题框架：

- 使用 continuous batching。
- 控制最大 batch 等待时间。
- 区分在线请求和离线批处理。
- 简单任务路由到小模型。
- 限制长上下文请求。
- 缓存 embedding 和高频结果。
- 监控 queue waiting time 和 TTFT。


## 8. Embedding

### Embedding 是什么

Embedding 是把文本、图片或其他对象映射成向量，语义相近的内容在向量空间中距离更近。

应用：

- 语义检索
- 文本聚类
- 推荐系统
- 去重
- RAG 召回

面试答法：

> Embedding 把非结构化文本变成可计算的向量。做 RAG 时，我们通常把文档 chunk 编成向量，用户 query 也编成向量，再用相似度搜索找相关文档。

### 相似度计算

常见方法：

- Cosine Similarity：看方向相似度。
- Dot Product：点积，受向量长度影响。
- Euclidean Distance：欧氏距离。

面试常答：

> 语义检索中常用 cosine 或 dot product。具体用哪个要看 embedding 模型训练时推荐的距离度量。

## 9. RAG 高频

### RAG 是什么

RAG，即 Retrieval-Augmented Generation，检索增强生成。它先从外部知识库检索相关内容，再把检索结果放进 prompt，让 LLM 基于这些材料回答。

面试答法：

> RAG 用外部知识补充 LLM 的上下文，解决知识更新、私有数据、可追溯引用等问题。典型流程是文档切分、向量化、入库、query 检索、rerank、拼 prompt、生成答案。

### RAG 基本流程

1. 文档解析：PDF、网页、Markdown、Word 等。
2. 文档切分：按段落、标题、token 数切 chunk。
3. 向量化：用 embedding 模型生成向量。
4. 建索引：存入向量数据库。
5. 查询改写：把用户问题改成更适合检索的 query。
6. 检索召回：top-k 相似度搜索。
7. 重排序：reranker 对候选片段重新打分。
8. 生成回答：把相关片段放入 prompt，让 LLM 回答。
9. 引用溯源：返回依据片段或文档来源。

### Chunk 怎么切

常见策略：

- 固定长度切分：简单，但可能切断语义。
- 按标题/段落切分：语义更完整。
- 滑动窗口 overlap：减少跨 chunk 信息丢失。
- 结构化切分：保留标题层级、页码、表格信息。

面试答法：

> Chunk 太大会引入噪声、占用上下文；太小会丢失语义。通常需要结合文档结构切分，并设置一定 overlap，最后通过检索效果评估调整 chunk size 和 top-k。

### RAG 为什么需要 Rerank

向量检索召回速度快，但可能只看语义相似，不一定最能回答问题。Reranker 通常用更强的交叉编码模型，对 query 和候选文档做精排。

面试答法：

> Retriever 负责多召回，reranker 负责精排序。这样可以兼顾速度和相关性。

### RAG 常见问题

- 检索不到：chunk 切分差、embedding 模型不适配、query 表达不一致。
- 检索到了但答错：prompt 没约束、模型没有引用证据、上下文太多。
- 答案不完整：top-k 太小、chunk 太碎、缺少多跳检索。
- 延迟高：向量库慢、rerank 太重、上下文太长。

优化方向：

- Query rewrite
- Hybrid search：BM25 + vector search
- Rerank
- Metadata filter
- Parent-child chunk
- 多轮检索
- 答案引用和置信度判断

### 向量数据库

常见能力：

- 存储向量和 metadata。
- 支持 ANN 近似最近邻搜索。
- 支持 filter，比如按时间、用户、文档类型过滤。

常见索引：

- HNSW
- IVF
- Flat

面试答法：

> 向量数据库的作用是高效做相似度检索。工程上除了向量本身，还要存文档 id、chunk id、来源、页码、权限等 metadata。

## 10. Prompt Engineering

### Prompt 基本结构

常见结构：

```text
角色：你是什么助手
任务：你要完成什么
上下文：可用材料
约束：不能编造、必须引用、输出格式
示例：few-shot examples
用户问题：真实输入
```

面试答法：

> Prompt 的目的不是写得花，而是明确任务、边界、格式和评判标准。生产环境里尤其要关注稳定性、可解析性和抗注入。

### Zero-shot / Few-shot

- Zero-shot：不给示例，直接让模型完成任务。
- Few-shot：给几个输入输出示例，让模型模仿格式和逻辑。

适用：

- 任务简单：zero-shot。
- 格式复杂、分类标准细：few-shot。

### 结构化输出

常见方式：

- 明确 JSON schema。
- 使用函数调用或工具调用。
- 输出后做 JSON parse 和校验。
- 失败时 retry 或让模型修复格式。

面试答法：

> 生产中不能只相信模型会按格式输出，要用 schema、parser、校验和重试机制保证稳定。

### Prompt Injection

Prompt Injection 是用户输入恶意指令，试图覆盖系统指令或泄露隐私。

防护：

- 系统指令和用户输入隔离。
- 不把敏感信息直接放入 prompt。
- 对工具调用做权限控制。
- 对 RAG 文档内容做不可信处理。
- 输出和工具参数做校验。

## 11. AI Agent 高频

### Agent 是什么

Agent 是能根据目标进行规划、调用工具、观察结果并继续行动的系统。

常见组成：

- LLM：决策和生成。
- Tools：搜索、数据库、代码执行、API。
- Memory：短期对话历史、长期用户偏好或任务状态。
- Planner：任务拆解。
- Executor：执行动作。
- Evaluator：检查结果是否达标。

面试答法：

> 普通 LLM 应用通常是一次输入一次输出，Agent 更强调循环决策：思考下一步、调用工具、观察结果、再决定下一步，直到任务完成或停止。

### Tool Calling / Function Calling

模型输出结构化的工具调用参数，由程序真正执行工具，再把结果返回给模型。

工程要点：

- 工具 schema 要清晰。
- 参数要校验。
- 工具要有超时和错误处理。
- 高风险工具要有人审或权限控制。
- 工具结果要简洁返回，避免上下文爆炸。

面试答法：

> 工具调用不是让模型直接执行代码，而是模型决定调用哪个工具和参数，后端负责校验、执行和返回结果。

### ReAct

ReAct 是 Reasoning + Acting，即模型交替进行推理和行动。

简化流程：

```text
Thought: 我需要查什么
Action: 调用工具
Observation: 得到结果
Thought: 根据结果决定下一步
Final: 输出答案
```

面试答法：

> ReAct 适合需要外部信息或多步操作的任务。它把推理和工具调用串起来，但要注意限制最大步数，防止死循环。

### Agent Memory

短期记忆：

- 当前对话历史
- 当前任务状态

长期记忆：

- 用户偏好
- 历史任务记录
- 可检索知识库

常见问题：

- 记忆污染
- 隐私泄露
- 召回不相关记忆
- 成本和延迟增加

### Agent 常见失败模式

- 工具选错。
- 参数生成错误。
- 循环调用停不下来。
- 没有验证工具结果。
- 把工具返回的错误当成事实。
- 对用户目标理解错。

解决方式：

- 限制最大迭代次数。
- 工具参数 schema 校验。
- 给工具加权限和超时。
- 增加 evaluator 或 rule-based guard。
- 对关键步骤让用户确认。

### Multi-Agent

Multi-Agent 是多个 agent 分工协作，例如 planner、researcher、coder、reviewer。

优点：

- 分工清晰。
- 可以互相检查。
- 复杂任务更容易拆解。

缺点：

- 成本高。
- 延迟高。
- 协作不稳定。
- 容易过度复杂。

面试答法：

> Multi-Agent 不一定比单 Agent 好。只有当任务确实需要多角色、多阶段检查时才值得使用，否则单 Agent 加工具和评估更简单稳定。

## 12. 时间复杂度与空间复杂度

时间复杂度和空间复杂度是手撕代码面试必问内容。回答算法题时，最后一定要主动说清楚：时间复杂度是多少、空间复杂度是多少、为什么。

### 时间复杂度是什么

时间复杂度描述算法运行时间随输入规模 `n` 增长的变化趋势，不关心具体运行了几毫秒，而关心规模变大后增长得快不快。

面试答法：

> 时间复杂度衡量的是算法执行步骤数量和输入规模之间的关系。我们通常用大 O 表示法，只保留增长最快的主项，忽略常数和低阶项。

例子：

```cpp
for (int i = 0; i < n; ++i) {
    cout << nums[i] << endl;
}
```

循环执行 `n` 次，所以时间复杂度是 O(n)。

### 空间复杂度是什么

空间复杂度描述算法运行过程中额外占用的内存随输入规模增长的变化趋势。

注意：

- 通常只算额外空间，不算输入本身。
- 输出数组是否计入空间复杂度，要看题目和面试官口径。
- 递归调用栈也算空间。

面试答法：

> 空间复杂度衡量的是算法额外使用的内存，比如哈希表、栈、队列、递归栈、DP 数组等。

### 常见复杂度从低到高

```text
O(1)        常数复杂度
O(log n)    对数复杂度
O(n)        线性复杂度
O(n log n)  常见于排序、分治
O(n^2)      双重循环
O(n^3)      三重循环
O(2^n)      子集、指数搜索
O(n!)       全排列
```

增长速度：

```text
O(1) < O(log n) < O(n) < O(n log n) < O(n^2) < O(2^n) < O(n!)
```

### 大 O 表示法

大 O 只保留主导增长项：

```text
O(3n)       -> O(n)
O(n + 100)  -> O(n)
O(n^2 + n)  -> O(n^2)
O(n^2 + m)  -> O(n^2 + m)
```

面试注意：

> 如果有两个不同规模的输入，比如数组长度是 `n`，字符串长度是 `m`，复杂度不能强行写成 O(n)，应该写 O(n + m) 或 O(nm)。

### O(1)

常数复杂度表示运行时间不随输入规模增长。

例子：

```cpp
int first = nums[0];
```

常见场景：

- 数组按下标访问。
- 哈希表平均查找。
- 栈顶元素访问。

注意：

> `unordered_map` 平均查找是 O(1)，但极端哈希冲突下最坏可能退化。

### O(log n)

对数复杂度通常来自每次把问题规模缩小一半。

典型题型：

- 二分查找。
- 平衡二叉搜索树查找。
- 堆的插入和删除。

例子：

```cpp
int binarySearch(vector<int>& nums, int target) {
    int left = 0, right = nums.size() - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (nums[mid] == target) return mid;
        if (nums[mid] < target) left = mid + 1;
        else right = mid - 1;
    }
    return -1;
}
```

每次搜索区间减半，所以时间复杂度 O(log n)。

### O(n)

线性复杂度通常表示遍历一次输入。

例子：

```cpp
int sum = 0;
for (int x : nums) {
    sum += x;
}
```

时间复杂度 O(n)，空间复杂度 O(1)。

### O(n log n)

常见于高效排序和分治。

典型场景：

- `sort(nums.begin(), nums.end())`
- 归并排序
- 快速排序平均情况
- 堆排序

面试答法：

> C++ STL 的 `sort` 平均和通常实现保证是 O(n log n)，很多题如果先排序再线性扫描，总时间就是 O(n log n)。

### O(n^2)

常见于双重循环。

例子：

```cpp
for (int i = 0; i < n; ++i) {
    for (int j = i + 1; j < n; ++j) {
        // check pair
    }
}
```

即使内层从 `i + 1` 开始，总次数约为 `n(n-1)/2`，仍然是 O(n^2)。

典型题：

- 暴力 Two Sum。
- 3Sum 排序后双指针是 O(n^2)。
- O(n^2) LIS DP。

### O(2^n)

指数复杂度常见于枚举所有选择。

典型题：

- 子集。
- 回溯搜索。
- 每个元素选或不选。

例子：

> n 个元素，每个元素有选和不选两种状态，总共有 `2^n` 个子集。

### O(n!)

阶乘复杂度常见于全排列。

例子：

> n 个不同元素的排列数量是 `n!`，所以生成所有排列至少需要 O(n!)。

### 递归复杂度怎么分析

递归复杂度看两点：

1. 递归调用次数。
2. 每次调用做多少额外工作。

二叉树 DFS：

```cpp
int maxDepth(TreeNode* root) {
    if (!root) return 0;
    return 1 + max(maxDepth(root->left), maxDepth(root->right));
}
```

每个节点访问一次，时间 O(n)。

递归栈深度等于树高，空间 O(h)。

- 平衡树：h = log n。
- 链状树：h = n。

### BFS / DFS 复杂度

树：

- 时间 O(n)，每个节点访问一次。
- 空间 O(h) 或 O(n)，取决于 DFS 递归栈或 BFS 队列。

图：

- 邻接表：时间 O(V + E)。
- 空间 O(V + E) 存图，O(V) 存 visited。

网格：

- 时间 O(mn)。
- 空间最坏 O(mn)。

### 哈希表复杂度

常见操作平均 O(1)：

```cpp
unordered_map<int, int> mp;
mp[x]++;
mp.count(x);
```

但要知道：

- 平均 O(1)。
- 最坏可能 O(n)。
- 面试中一般按平均 O(1) 分析。

典型题：

- Two Sum：时间 O(n)，空间 O(n)。
- Subarray Sum Equals K：时间 O(n)，空间 O(n)。

### 堆复杂度

`priority_queue`：

- 插入：O(log n)。
- 删除堆顶：O(log n)。
- 访问堆顶：O(1)。

Top K：

```cpp
priority_queue<int, vector<int>, greater<int>> heap;
```

维护大小为 k 的小根堆：

- 每个元素最多一次 push/pop，单次 O(log k)。
- 总时间 O(n log k)。
- 空间 O(k)。

### 排序复杂度

C++：

```cpp
sort(nums.begin(), nums.end());
```

通常按 O(n log n) 分析。

常见组合：

- 排序 + 一次遍历：O(n log n)。
- 排序 + 双指针：O(n log n + n) = O(n log n)。
- 3Sum：排序 O(n log n)，外层 + 双指针 O(n^2)，总 O(n^2)。

### 动态规划复杂度

DP 复杂度通常看状态数量和每个状态的转移成本。

公式：

```text
时间复杂度 = 状态数 * 每个状态转移成本
空间复杂度 = dp 数组大小
```

例子：零钱兑换

```cpp
vector<int> dp(amount + 1, amount + 1);
for (int x = 1; x <= amount; ++x) {
    for (int coin : coins) {
        if (coin <= x) dp[x] = min(dp[x], dp[x - coin] + 1);
    }
}
```

状态数是 `amount`，每个状态枚举 `coins.size()` 个硬币。

- 时间 O(amount * n)。
- 空间 O(amount)。

### 空间复杂度常见来源

常见额外空间：

- 哈希表：O(n)。
- 栈/队列：O(n)。
- DP 数组：O(n)、O(mn)。
- 递归栈：O(depth)。
- 排序：可能 O(log n) 或 O(n)，看实现。

例子：

```cpp
vector<int> dp(n, 0);              // O(n)
vector<vector<int>> grid(m, vector<int>(n)); // O(mn)
unordered_map<int, int> mp;        // O(n)
```

### 原地算法

原地算法通常指不使用和输入规模相关的额外空间。

例子：反转链表

```cpp
ListNode* prev = nullptr;
ListNode* cur = head;
while (cur) {
    ListNode* nxt = cur->next;
    cur->next = prev;
    prev = cur;
    cur = nxt;
}
```

只用了几个指针，所以空间 O(1)。

### 面试中怎么回答复杂度

推荐话术：

> 这个算法主循环遍历数组一次，每个元素只处理常数次，所以时间复杂度是 O(n)。额外用了一个哈希表，最坏情况下会存 n 个元素，所以空间复杂度是 O(n)。

树题话术：

> 每个节点只访问一次，所以时间复杂度 O(n)。递归栈深度等于树高 h，所以空间复杂度 O(h)，最坏链状树是 O(n)，平衡树是 O(log n)。

图题话术：

> 使用邻接表建图并做 BFS，每个点和每条边最多处理一次，所以时间复杂度 O(V + E)，空间复杂度 O(V + E)。

### 高频坑

- 两个独立循环 `O(n) + O(n)` 仍是 O(n)。
- 双重循环不一定总是 O(n^2)，如果双指针整体只移动 n 次，就是 O(n)。
- 递归栈要算空间。
- `sort` 通常要算 O(n log n)。
- 输出结果很大时，输出本身也可能影响复杂度。
- 哈希表一般说平均 O(1)，严谨时补一句最坏会退化。
- 如果有两个输入规模，写 O(n + m)，不要偷懒写 O(n)。

### 高频开放题：为什么滑动窗口是 O(n)

答题框架：

- 虽然有 while 嵌套在 for 里，但 left 和 right 都只单调右移。
- 每个元素最多被 right 加入一次，被 left 移出一次。
- 所以总操作次数是 O(2n)，简化为 O(n)。

### 高频开放题：为什么单调栈是 O(n)

答题框架：

- 每个元素最多入栈一次。
- 每个元素最多出栈一次。
- 所以所有 push/pop 总次数是 O(n)。

### 高频开放题：递归空间复杂度怎么算

答题框架：

- 递归空间主要来自调用栈。
- 栈深度等于递归深度。
- 二叉树 DFS 是 O(h)，h 是树高。
- 回溯如果 path 长度为 n，则 path 和递归栈通常都是 O(n)，但输出结果不一定计入额外空间。

## 13. TCP/IP 与 HTTP 高频

AI 应用研发虽然重点是 LLM 和业务，但前后端、模型网关、SSE 流式输出、文件上传、API 调用都离不开网络基础。

### TCP/IP 分层

常见四层模型：

```text
应用层：HTTP、DNS、WebSocket、SMTP
传输层：TCP、UDP
网络层：IP、ICMP
链路层：以太网、Wi-Fi
```

面试答法：

> TCP/IP 是互联网通信的基础协议族。HTTP 属于应用层，TCP/UDP 属于传输层，IP 负责寻址和路由。我们平时写接口主要接触 HTTP，但性能、稳定性和连接问题经常要理解 TCP。

### TCP 和 UDP 的区别

TCP：

- 面向连接。
- 可靠传输。
- 保证顺序。
- 有拥塞控制和流量控制。
- 适合 HTTP、文件传输、数据库连接等。

UDP：

- 无连接。
- 不保证可靠和顺序。
- 开销小、延迟低。
- 适合直播、游戏、语音、DNS、QUIC 等。

面试答法：

> TCP 牺牲一部分延迟换可靠性，UDP 牺牲可靠性换低延迟。普通 Web API 基本跑在 TCP 上，而实时音视频或 QUIC/HTTP3 会更多用 UDP。

### TCP 三次握手

三次握手用于建立可靠连接。

```text
1. Client -> Server: SYN
2. Server -> Client: SYN + ACK
3. Client -> Server: ACK
```

为什么需要三次：

- 双方都要确认自己能发送、能接收。
- 防止历史失效连接请求被误认为新连接。

面试答法：

> 第一次客户端证明自己能发；第二次服务端证明自己能收也能发；第三次客户端证明自己能收。三次后双方都确认收发能力正常。

### TCP 四次挥手

四次挥手用于关闭连接。

```text
1. Client -> Server: FIN
2. Server -> Client: ACK
3. Server -> Client: FIN
4. Client -> Server: ACK
```

为什么通常是四次：

> TCP 是全双工连接，一方不发数据了，不代表另一方也已经发完。所以关闭两个方向的数据流通常要分别确认。

### TIME_WAIT

主动关闭连接的一方会进入 TIME_WAIT。

作用：

- 确保最后一个 ACK 能被对方收到。
- 让旧连接中的延迟报文在网络中自然消失，避免影响新连接。

常见追问：

- TIME_WAIT 太多怎么办？
  可以从连接复用、keep-alive、调整系统参数、负载均衡和连接池角度优化，但不能粗暴消除。

### TCP 可靠性如何保证

机制：

- 序列号。
- ACK 确认。
- 超时重传。
- 滑动窗口。
- 流量控制。
- 拥塞控制。

面试答法：

> TCP 通过序列号和 ACK 确认数据是否到达，通过重传处理丢包，通过滑动窗口提高吞吐，通过流量控制和拥塞控制避免压垮接收方和网络。

### HTTP 是什么

HTTP 是应用层协议，用于客户端和服务端之间传输超文本和 API 数据。现代 Web 前后端接口大多基于 HTTP。

一次 HTTP 请求通常包括：

- 请求方法：GET、POST、PUT、DELETE 等。
- URL。
- Headers。
- Body。

一次 HTTP 响应通常包括：

- 状态码。
- Headers。
- Body。

### HTTP 常见方法

GET：

- 获取资源。
- 参数通常放 URL query。
- 一般不应该有副作用。

POST：

- 创建资源或提交操作。
- 参数通常放 body。
- 可能有副作用。

PUT：

- 整体更新资源。

PATCH：

- 局部更新资源。

DELETE：

- 删除资源。

面试答法：

> GET 偏查询，POST 偏提交和创建，PUT 偏整体替换，PATCH 偏局部修改，DELETE 删除资源。RESTful API 会用这些方法表达资源操作语义。

### HTTP 状态码

常见状态码：

```text
200 OK：请求成功
201 Created：创建成功
204 No Content：成功但无响应体
301 Moved Permanently：永久重定向
302 Found：临时重定向
304 Not Modified：缓存未变
400 Bad Request：请求参数错误
401 Unauthorized：未登录或认证失败
403 Forbidden：无权限
404 Not Found：资源不存在
409 Conflict：资源冲突
429 Too Many Requests：请求过多，被限流
500 Internal Server Error：服务端错误
502 Bad Gateway：网关收到上游错误
503 Service Unavailable：服务不可用
504 Gateway Timeout：网关超时
```

AI 应用里常见：

- `400`：prompt 参数、文件格式、JSON schema 错。
- `401/403`：API key 或用户权限问题。
- `429`：模型 API 限流。
- `500`：后端程序异常。
- `502/504`：模型服务、网关或上游超时。

### HTTP Header

常见 header：

```text
Content-Type：请求或响应体格式，如 application/json
Authorization：认证信息，如 Bearer token
Cookie：浏览器携带的 cookie
Cache-Control：缓存策略
User-Agent：客户端信息
Accept：客户端能接受的响应类型
Origin / Referer：来源信息
```

AI 应用常见：

- `Authorization: Bearer xxx` 用于 API 鉴权。
- `Content-Type: application/json` 用于普通 JSON 请求。
- `Content-Type: text/event-stream` 用于 SSE 流式输出。

### HTTP 和 HTTPS

HTTP 明文传输，HTTPS = HTTP + TLS 加密。

HTTPS 提供：

- 加密：防止内容被窃听。
- 完整性：防止内容被篡改。
- 身份认证：通过证书确认服务端身份。

面试答法：

> 生产环境必须使用 HTTPS，尤其是登录态、API key、用户上传文件和 LLM 对话内容都可能包含敏感信息。

### HTTP/1.1、HTTP/2、HTTP/3

HTTP/1.1：

- 支持 keep-alive。
- 同一个连接上请求仍容易队头阻塞。

HTTP/2：

- 二进制分帧。
- 多路复用。
- Header 压缩。
- 通常仍基于 TCP。

HTTP/3：

- 基于 QUIC。
- QUIC 基于 UDP。
- 减少 TCP 层队头阻塞。
- 连接建立更快。

面试答法：

> HTTP/2 通过多路复用提升并发性能，但因为基于 TCP，丢包时仍可能受 TCP 队头阻塞影响。HTTP/3 基于 QUIC/UDP，在弱网环境下表现更好。

### 长连接 Keep-Alive

HTTP keep-alive 允许多个请求复用同一个 TCP 连接，减少频繁三次握手的成本。

工程意义：

- 降低延迟。
- 减少连接创建开销。
- 对模型网关、后端调用外部 API 很重要。

### Cookie、Session、Token

Cookie：

- 存在浏览器端。
- 每次请求自动携带到同域服务端。

Session：

- 服务端保存用户登录状态。
- 客户端通常只保存 session id。

Token：

- 常见是 JWT 或 API token。
- 客户端请求时放在 header 中。

面试答法：

> Cookie 是浏览器存储和自动携带机制，Session 是服务端状态管理，Token 更适合前后端分离和 API 鉴权。

### CORS 跨域

浏览器出于安全策略，限制网页向不同源发送请求。不同源指协议、域名、端口任一不同。

常见响应头：

```text
Access-Control-Allow-Origin
Access-Control-Allow-Methods
Access-Control-Allow-Headers
Access-Control-Allow-Credentials
```

面试答法：

> CORS 是浏览器安全策略，不是后端接口本身不能访问。前后端分离时，如果前端域名和后端域名不同，后端需要正确配置 CORS。

### RESTful API

RESTful 是一种接口设计风格，把业务对象看成资源，通过 URL 表示资源，通过 HTTP 方法表示操作。

例子：

```text
GET    /api/conversations
POST   /api/conversations
GET    /api/conversations/{id}
DELETE /api/conversations/{id}
POST   /api/conversations/{id}/messages
```

面试答法：

> RESTful 的重点是资源建模清晰、方法语义明确、状态码合理，而不是简单把所有接口都写成 POST。

### SSE

SSE，即 Server-Sent Events，是服务端向浏览器单向推送事件流的机制。

特点：

- 基于 HTTP。
- 服务端到客户端单向推送。
- 浏览器原生支持 `EventSource`。
- 适合 ChatGPT 这类 token 流式输出。

响应头：

```text
Content-Type: text/event-stream
Cache-Control: no-cache
Connection: keep-alive
```

面试答法：

> LLM Chat 常用 SSE，因为模型输出是服务端持续推给前端，单向流就够了，实现比 WebSocket 简单。

### WebSocket

WebSocket 是全双工通信协议，客户端和服务端可以互相实时发送消息。

适合：

- 聊天室。
- 协同编辑。
- 实时游戏。
- 需要双向实时通信的 Agent 控制台。

SSE vs WebSocket：

```text
SSE：单向、简单、适合 LLM 流式输出
WebSocket：双向、复杂、适合实时互动
```

### 文件上传

常见方式：

- `multipart/form-data`：表单文件上传。
- 直传对象存储：前端拿签名 URL 后直接上传到 OSS/S3。
- 分片上传：大文件上传更稳定。

AI 应用场景：

- 上传 PDF 进入 RAG 知识库。
- 上传图片给多模态模型。
- 上传音频做 ASR。

### HTTP 缓存

常见 header：

- `Cache-Control`
- `ETag`
- `Last-Modified`
- `If-None-Match`
- `If-Modified-Since`

状态码：

- `304 Not Modified` 表示资源没变，可以使用缓存。

AI 应用注意：

- 静态资源可以缓存。
- 用户私有问答结果要谨慎缓存。
- 带权限的数据不能跨用户缓存。

### 幂等性

幂等指同一个请求执行一次和执行多次的结果一致。

通常：

- GET 幂等。
- PUT 幂等。
- DELETE 通常幂等。
- POST 通常不幂等。

AI 应用注意：

> LLM 工具调用、支付、发邮件、创建任务这类操作要特别注意幂等，重试可能导致重复执行。

### API 超时与重试

常见策略：

- 设置连接超时和读取超时。
- 对短暂网络错误做有限重试。
- 使用指数退避。
- 对非幂等操作谨慎重试。
- 对长任务改成异步任务接口。

AI 应用：

- 模型生成可能很慢，要区分接口超时和用户取消。
- 工具调用要有 timeout。
- 多个上游失败时要降级或返回可理解错误。

### DNS

DNS 负责把域名解析成 IP 地址。

访问一个 URL 的大致过程：

1. DNS 解析域名得到 IP。
2. 建立 TCP 连接。
3. HTTPS 场景进行 TLS 握手。
4. 发送 HTTP 请求。
5. 服务端处理并返回响应。
6. 浏览器解析响应。

### 面试开放题：从输入 URL 到页面展示发生了什么

答题框架：

1. 浏览器解析 URL。
2. 查缓存。
3. DNS 解析域名。
4. 建立 TCP 连接，HTTPS 还要 TLS 握手。
5. 发送 HTTP 请求。
6. 服务端路由、业务处理、数据库查询。
7. 返回 HTTP 响应。
8. 浏览器解析 HTML、CSS、JS。
9. 构建 DOM/CSSOM，渲染页面。
10. JS 执行，可能继续发起 API 请求。

### 面试开放题：为什么 LLM 流式输出常用 SSE

答题框架：

- LLM 生成是逐 token 产生。
- 前端希望边生成边展示，降低用户等待感。
- SSE 基于 HTTP，服务端单向推送，足够满足 token 流。
- 相比 WebSocket，SSE 实现简单、调试方便、浏览器支持好。
- 如果需要双向实时控制或复杂协作，再考虑 WebSocket。

## 14. 操作系统与并发编程

AI 应用研发不一定会深挖内核，但经常会问进程线程、并发、锁、异步、线程池，因为这些直接影响后端接口、模型调用、任务队列和流式输出的稳定性。

### 进程和线程

进程：

- 操作系统资源分配的基本单位。
- 有独立地址空间。
- 进程之间通信成本较高。
- 一个程序运行起来通常就是一个或多个进程。

线程：

- CPU 调度的基本单位。
- 同一进程内的线程共享进程资源，如内存、文件描述符。
- 线程切换比进程轻量，但共享内存会带来并发安全问题。

面试答法：

> 进程更像资源容器，线程是执行流。同一进程里的多个线程共享内存，所以通信方便，但也需要锁来保护共享数据。

### 协程

协程是用户态的轻量级执行单元，通常由程序运行时调度，而不是直接由操作系统调度。

特点：

- 切换成本低。
- 适合大量 I/O 等待任务。
- 不适合直接提升 CPU 密集任务性能。

面试答法：

> 协程适合高并发 I/O 场景，比如同时等待很多网络请求。它的优势是减少线程阻塞和上下文切换开销，但 CPU 密集任务还是需要多线程或多进程。

### 并发和并行

并发：

- 多个任务在同一时间段内交替推进。
- 不一定同时执行。

并行：

- 多个任务在同一时刻真正同时执行。
- 需要多核 CPU 或多台机器。

面试答法：

> 并发强调任务调度能力，并行强调真正同时执行。单核 CPU 可以并发，但不能真正并行。

### 同步、异步、阻塞、非阻塞

同步 / 异步关注调用结果如何返回：

- 同步：调用方主动等待结果。
- 异步：调用方发起任务后继续做别的事，结果通过回调、Future、事件等方式返回。

阻塞 / 非阻塞关注等待时线程是否被挂起：

- 阻塞：没有结果时线程停住。
- 非阻塞：没有结果时立即返回，调用方可以稍后再查。

面试答法：

> 同步异步说的是调用方式，阻塞非阻塞说的是线程状态。它们不是一组完全等价的概念。

AI 应用例子：

- 同步阻塞：后端直接等待 LLM 完整返回后再响应。
- 异步流式：后端边接收模型 token 边通过 SSE 推给前端。
- 异步任务：上传大文档后创建后台入库任务，前端轮询任务状态。

### 上下文切换

上下文切换是 CPU 从一个任务切到另一个任务时保存和恢复执行现场。

代价：

- 保存寄存器和程序计数器。
- 切换内存映射或线程上下文。
- 可能导致缓存失效。

面试答法：

> 线程不是越多越好。线程过多会导致频繁上下文切换，CPU 时间浪费在调度上，反而降低吞吐。

### 临界区和竞态条件

临界区：

- 访问共享资源的代码区域。

竞态条件：

- 多个线程同时读写共享数据，结果依赖执行顺序，导致不确定错误。

例子：

```cpp
count++;
```

这不是原子操作，通常包含读、加、写三个步骤，多线程下可能丢更新。

### 锁 Mutex

锁用于保护共享资源，确保同一时刻只有一个线程进入临界区。

C++ 示例：

```cpp
mutex mtx;
int count = 0;

void add() {
    lock_guard<mutex> lock(mtx);
    ++count;
}
```

面试答法：

> 锁能保证并发安全，但会降低并发度。锁粒度太大性能差，锁粒度太小容易复杂和死锁。

### 死锁

死锁是多个线程互相等待对方持有的资源，导致都无法继续执行。

死锁四个必要条件：

1. 互斥：资源一次只能被一个线程持有。
2. 占有并等待：线程持有资源的同时等待其他资源。
3. 不可抢占：资源不能被强行夺走。
4. 循环等待：多个线程形成环形等待关系。

避免方式：

- 固定加锁顺序。
- 尽量减少同时持有多个锁。
- 使用超时锁。
- 用更高层并发结构，如队列、线程池。

面试答法：

> 死锁最常见的解决思路是破坏循环等待，比如所有线程都按相同顺序加锁。

### 读写锁

读写锁允许多个读线程同时访问，但写线程独占。

适合：

- 读多写少的场景。
- 配置缓存、知识库 metadata 缓存等。

注意：

- 写多时读写锁不一定比普通锁好。
- 可能出现写线程饥饿，需要看具体实现。

### 原子操作

原子操作是不可被打断的操作。

C++ 示例：

```cpp
atomic<int> count = 0;
count++;
```

适合：

- 简单计数器。
- 状态标记。
- 无锁数据结构基础。

注意：

> 原子操作适合简单共享变量，不适合复杂临界区。复杂逻辑通常仍需要锁。

### 线程池

线程池预先创建一组工作线程，任务到来后放入队列，由线程池调度执行。

优点：

- 避免频繁创建和销毁线程。
- 控制并发度。
- 防止请求过多把系统拖垮。

AI 应用场景：

- 并发调用多个工具。
- 后台处理文档解析和 embedding。
- 执行耗时但可并行的 I/O 任务。

面试答法：

> 线程池的核心是任务队列 + 固定数量工作线程。它不是让任务无限并发，而是控制系统同时处理多少任务。

### 任务队列

任务队列用于异步处理耗时任务。

适合：

- 文档入库。
- 批量 embedding。
- 视频/音频处理。
- 邮件发送。
- 定时评估任务。

常见状态：

```text
pending -> running -> success / failed
```

面试答法：

> 对耗时任务，不建议让 HTTP 请求一直阻塞等待。可以创建任务并返回 task_id，前端轮询或订阅任务状态。

### I/O 密集和 CPU 密集

I/O 密集：

- 时间主要花在网络、磁盘、数据库等待。
- 适合异步、协程、线程池。

CPU 密集：

- 时间主要花在计算。
- 适合多进程、多线程并行、GPU 或 C++ 优化。

AI 应用例子：

- 调模型 API、查向量库、读文件：I/O 密集。
- 本地 embedding、rerank、图片处理：可能是 CPU/GPU 密集。

### 生产者消费者模型

生产者负责生成任务，消费者负责处理任务，中间通过队列解耦。

例子：

```text
用户上传 PDF -> 生产入库任务 -> 队列 -> worker 解析、切分、embedding、入库
```

优点：

- 削峰。
- 解耦。
- 失败可重试。
- 方便横向扩容 worker。

### 多进程和多线程怎么选

多线程：

- 共享内存方便。
- 适合 I/O 密集。
- 要注意线程安全。

多进程：

- 隔离性好。
- 一个进程崩溃不一定影响其他进程。
- 适合 CPU 密集或需要隔离的任务。

面试答法：

> 如果任务是 I/O 密集，线程或协程通常更合适；如果是 CPU 密集，多进程能更好利用多核，也能避免某些语言运行时的全局锁限制。

### Python GIL

GIL 是 CPython 的全局解释器锁，同一时刻通常只允许一个线程执行 Python 字节码。

影响：

- Python 多线程不适合提升 CPU 密集任务性能。
- 对 I/O 密集任务仍然有用，因为等待 I/O 时会释放 GIL。
- CPU 密集任务可用多进程、C++ 扩展、NumPy、GPU 等方式优化。

面试答法：

> Python 多线程不是完全没用，它对 I/O 密集任务有效；但 CPU 密集任务通常要用多进程或底层释放 GIL 的计算库。

### C++ 并发常见工具

常见类型：

```cpp
std::thread
std::mutex
std::lock_guard
std::unique_lock
std::condition_variable
std::atomic
std::future
std::async
```

条件变量示例思想：

> 一个线程等待条件满足，另一个线程修改条件后通知它。常用于生产者消费者模型。

### AI 应用中的并发设计

场景 1：并发工具调用

```text
用户问题需要查天气、查数据库、查搜索结果
可以并发调用多个工具
最后聚合结果给模型
```

注意：

- 每个工具要有 timeout。
- 失败要有 fallback。
- 聚合时要保留错误信息。

场景 2：文档入库

```text
上传文件 -> 后台任务 -> 多 worker 解析/切分/embedding -> 写向量库
```

注意：

- 控制 embedding 并发，避免 API 限流。
- 失败任务可重试。
- 入库过程要记录进度。

场景 3：LLM 流式输出

```text
后端请求模型流
模型返回 token chunk
后端通过 SSE 推给前端
用户点击停止时取消请求
```

注意：

- 支持取消。
- 处理断连。
- 记录 partial output。

### 高频开放题：如何设计一个并发安全的计数器

答题框架：

- 简单计数用 `atomic<int>`。
- 如果还有复杂逻辑，用 mutex 保护临界区。
- 高并发下可以分片计数，最后汇总，降低锁竞争。

### 高频开放题：如何处理 LLM 批量调用限流

答题框架：

- 用队列控制请求进入速度。
- 线程池/协程池控制并发数。
- 对 429 做指数退避重试。
- 按用户或任务设置 quota。
- 记录失败并支持恢复。

### 高频开放题：为什么不能一个请求创建一个线程

答题框架：

- 线程创建销毁有成本。
- 线程过多导致上下文切换变多。
- 内存占用上升。
- 下游服务可能被打爆。
- 应该用线程池、异步 I/O、队列和限流控制并发。

## 15. Docker / 部署

这一章用于回答“你会不会把项目跑起来、部署起来、排查部署问题”。AI 应用研发面试里，Docker 经常和后端服务、向量数据库、Redis、模型服务一起问。

### Docker 是什么

Docker 是容器化工具，可以把应用和运行环境一起打包，保证在不同机器上运行结果一致。

核心概念：

- Image：镜像，应用运行环境的只读模板。
- Container：容器，由镜像启动起来的运行实例。
- Dockerfile：构建镜像的脚本。
- Volume：数据挂载，用于持久化。
- Network：容器网络，用于容器间通信。

面试答法：

> Docker 解决的是环境一致性和部署隔离问题。把代码、依赖和运行配置打包成镜像后，可以在开发、测试、生产环境中更稳定地运行。

### 镜像和容器的区别

镜像：

- 静态模板。
- 类似“安装包”。
- 不能直接修改运行状态。

容器：

- 镜像运行起来后的进程。
- 有自己的文件系统、网络和进程空间。
- 可以启动、停止、删除。

面试答法：

> 镜像是静态的，容器是运行中的。一个镜像可以启动多个容器。

### Dockerfile

Dockerfile 用来定义如何构建镜像。

Python 后端示例：

```dockerfile
FROM python:3.11-slim

WORKDIR /app
COPY requirements.txt .
RUN pip install --no-cache-dir -r requirements.txt

COPY . .
EXPOSE 8000

CMD ["uvicorn", "main:app", "--host", "0.0.0.0", "--port", "8000"]
```

常见指令：

- `FROM`：基础镜像。
- `WORKDIR`：工作目录。
- `COPY`：复制文件。
- `RUN`：构建时执行命令。
- `EXPOSE`：声明端口。
- `CMD`：容器启动时默认命令。

### Docker 常用命令

构建镜像：

```bash
docker build -t my-app .
```

运行容器：

```bash
docker run -p 8000:8000 my-app
```

查看容器：

```bash
docker ps
docker ps -a
```

查看日志：

```bash
docker logs -f container_name
```

进入容器：

```bash
docker exec -it container_name bash
```

停止和删除：

```bash
docker stop container_name
docker rm container_name
```

### 端口映射

容器内部服务监听自己的端口，宿主机需要通过端口映射访问。

```bash
docker run -p 8080:8000 my-app
```

含义：

```text
宿主机 8080 -> 容器 8000
```

面试答法：

> 容器内部端口默认不等于外部可访问端口，需要通过 `-p host_port:container_port` 映射。

### Volume 数据持久化

容器删除后，容器内部文件通常也会丢失。数据库、上传文件、向量库索引需要挂载 volume。

示例：

```bash
docker run -v ./data:/app/data my-app
```

AI 应用场景：

- 持久化上传文件。
- 持久化向量数据库数据。
- 持久化模型缓存。
- 保存日志。

### 环境变量

生产中不要把密钥写死在代码里，通常用环境变量传入。

```bash
docker run -e OPENAI_API_KEY=xxx my-app
```

Docker Compose 中：

```yaml
environment:
  - OPENAI_API_KEY=${OPENAI_API_KEY}
```

注意：

> API Key、数据库密码、JWT secret 不应该提交到 GitHub。

### Docker Compose

Docker Compose 用来编排多个容器。

AI 应用常见组合：

```text
frontend
backend
postgres
redis
vector-db
model-server
```

示例：

```yaml
services:
  backend:
    build: .
    ports:
      - "8000:8000"
    environment:
      - REDIS_URL=redis://redis:6379
    depends_on:
      - redis

  redis:
    image: redis:7
    ports:
      - "6379:6379"
```

面试答法：

> 单个服务用 Docker 就够，多服务本地联调用 Docker Compose 更方便，比如后端、Redis、数据库、向量库一起启动。

### 容器网络

在同一个 Docker Compose 网络里，服务可以用服务名互相访问。

例子：

```text
backend 访问 redis，不写 localhost，而写 redis:6379
```

常见坑：

> 在容器里写 `localhost` 指的是容器自己，不是宿主机，也不是其他容器。

### 部署一个 AI 应用的典型结构

```text
用户浏览器
-> Nginx
-> 前端静态资源
-> 后端 API
-> Redis / SQL / Vector DB
-> 外部 LLM API 或本地模型服务
```

如果本地部署模型：

```text
backend -> model gateway -> vLLM/TGI -> GPU model
```

### Nginx

Nginx 常用于：

- 反向代理。
- 静态文件服务。
- HTTPS 终止。
- 负载均衡。
- 请求体大小限制。
- 超时配置。

反向代理直观理解：

```text
用户访问 https://example.com/api
Nginx 转发到 backend:8000
```

面试答法：

> Nginx 通常站在服务前面，负责转发请求、处理 HTTPS、服务静态资源和做基础负载均衡。

### 部署时常见配置

必须关注：

- 端口。
- 环境变量。
- 数据库连接。
- Redis 地址。
- API Key。
- 日志目录。
- 上传文件目录。
- 超时时间。
- CORS。
- HTTPS。

### 服务启动失败怎么排查

排查顺序：

1. 看容器是否在运行：`docker ps -a`。
2. 看日志：`docker logs`。
3. 看端口映射是否正确。
4. 看环境变量是否缺失。
5. 看依赖服务是否启动，比如 Redis/DB。
6. 进入容器检查文件和命令。
7. 检查网络访问和 DNS。

面试答法：

> 部署排查先看进程和日志，再看端口、环境变量、依赖服务和网络。不要一上来就改代码。

### AI 项目部署常见坑

- API Key 写进代码，被提交到仓库。
- 容器里用 `localhost` 访问另一个容器。
- 没挂载 volume，数据随容器删除丢失。
- 后端超时时间太短，LLM 还没返回就断开。
- Nginx 没配置流式响应，SSE 被缓冲。
- 上传文件大小超过 Nginx 限制。
- Docker 镜像太大，构建和部署慢。
- 没有健康检查和重启策略。

### 面试开放题：如何部署一个 RAG 应用

答题框架：

1. 前端构建成静态资源，用 Nginx 托管。
2. 后端 API 用 Docker 部署。
3. Redis 做缓存、限流和任务状态。
4. SQL 存用户、文档 metadata、权限。
5. 向量数据库存 chunk embedding。
6. 对接外部 LLM API 或本地 vLLM。
7. 配置环境变量、日志、监控、HTTPS。
8. 用 Docker Compose 或 Kubernetes 编排服务。

## 16. LLM 应用后端

### 一个 LLM 应用后端通常包含什么

核心模块：

- API 层：接收请求、鉴权、限流。
- Prompt 构造层：拼接 system、history、RAG context。
- Model Gateway：统一调用不同模型供应商。
- Tool 层：封装外部 API、数据库、搜索等。
- RAG 层：检索、rerank、引用。
- Session 层：管理会话历史。
- Logging 层：记录请求、输出、错误、token 用量。
- Eval 层：质量评估和回归测试。

### 流式输出

LLM 输出通常较慢，前端体验上会使用流式输出。

常见技术：

- SSE：Server-Sent Events，适合服务端单向推送文本流。
- WebSocket：双向通信，适合实时交互更复杂的场景。

面试答法：

> Chat 类应用常用 SSE，因为实现简单、适合 token 流式返回。如果需要双向实时通信或多人协作，可以考虑 WebSocket。

### 限流与重试

为什么需要：

- 防止用户刷接口。
- 控制模型成本。
- 避免外部 API 瞬时失败。

常见策略：

- 用户级限流。
- IP 级限流。
- 请求队列。
- 指数退避重试。
- 熔断和降级。

注意：

> LLM 请求不适合无限重试，因为成本高且可能重复执行工具。工具调用尤其要注意幂等性。

### 缓存

可缓存内容：

- Embedding 结果。
- RAG 检索结果。
- 相同 prompt 的模型输出。
- 用户 session 摘要。

注意：

- 个性化回答不一定能共享缓存。
- 涉及权限的数据不能跨用户缓存。
- 模型输出缓存要考虑版本、prompt 和参数。

### 日志与可观测性

需要记录：

- request id
- user id
- prompt 版本
- model name
- latency
- token usage
- tool calls
- retrieval chunks
- error message
- user feedback

面试答法：

> LLM 应用很难只靠传统日志定位问题，需要把 prompt、检索结果、工具调用链路和模型输出都关联起来看。

## 17. 前端高频

### Chat UI 关键点

功能：

- 消息列表
- 输入框
- 发送按钮
- 流式输出
- 重新生成
- 停止生成
- 复制答案
- 引用来源展示
- loading / error 状态

工程关注：

- 长文本换行。
- Markdown 渲染。
- 代码块高亮。
- 滚动到底部。
- 流式增量渲染。
- 请求取消。

### 前端如何处理流式输出

SSE 示例思路：

```text
前端发起请求
后端逐 token 返回 event
前端收到 chunk 后追加到当前 assistant message
结束后标记消息完成
```

常见问题：

- 中途断连。
- 用户点击停止。
- 多个请求并发导致消息错乱。
- Markdown 流式渲染时格式未闭合。

### 状态管理

常见状态：

- 当前会话 id
- 消息数组
- 输入框内容
- loading 状态
- error 状态
- 当前正在生成的 message id
- 引用来源

面试答法：

> Chat 前端的关键是把“消息状态”和“请求状态”分清楚。流式输出时要能定位当前 assistant message，并逐步追加内容。

### 前端安全

注意：

- Markdown 渲染要防 XSS。
- 不在前端存 API Key。
- 用户上传文件要限制类型和大小。
- 引用链接要做安全处理。
- 敏感配置放后端。

## 18. 数据库 / SQL 深挖

这一章用于回答“你会不会设计和使用数据库”。AI 应用里 SQL 常用于用户、权限、文档 metadata、任务状态、对话记录、评估结果等结构化数据。

### SQL / NoSQL / Vector DB / Object Storage 怎么选

SQL：

- 结构化数据。
- 强事务。
- 复杂查询。
- 用户、权限、订单、文档 metadata、任务状态。

NoSQL：

- schema 灵活。
- 半结构化数据。
- 会话、日志、事件、JSON 文档。

Vector DB：

- 存 embedding。
- 做语义相似度检索。
- RAG chunk 召回。

Object Storage：

- 存原始文件。
- PDF、图片、音频、视频、模型文件。

面试答法：

> LLM 应用通常不是只用一种数据库。用户权限和任务状态放 SQL，原始文件放对象存储，向量放向量库，缓存和限流用 Redis。

### 关系型数据库

关系型数据库用表组织数据，表之间可以通过主键、外键建立关系。

常见数据库：

- MySQL。
- PostgreSQL。
- SQLite。

适合：

- 用户系统。
- 权限系统。
- 交易数据。
- 文档 metadata。
- 需要事务一致性的业务。

### 表设计

设计表时要考虑：

- 主键。
- 字段类型。
- 是否允许为空。
- 默认值。
- 索引。
- 唯一约束。
- 创建时间和更新时间。

文档表例子：

```sql
CREATE TABLE documents (
    id BIGINT PRIMARY KEY,
    user_id BIGINT NOT NULL,
    title VARCHAR(255) NOT NULL,
    storage_url TEXT NOT NULL,
    status VARCHAR(32) NOT NULL,
    created_at TIMESTAMP NOT NULL,
    updated_at TIMESTAMP NOT NULL
);
```

### 主键和外键

主键：

- 唯一标识一行数据。
- 不能重复。
- 通常不可为空。

外键：

- 表示表之间的关联。
- 例如 `documents.user_id` 对应 `users.id`。

工程注意：

> 外键能保证一致性，但在高并发或复杂分库场景中，有些团队会用应用层保证关系，减少数据库约束成本。

### 索引

索引用于加速查询。

直观理解：

> 没有索引时，数据库可能要全表扫描；有索引时，可以像查字典一样快速定位数据。

常见索引：

- B+Tree 索引。
- 哈希索引。
- 唯一索引。
- 联合索引。
- 全文索引。

常见建索引字段：

- `user_id`
- `document_id`
- `created_at`
- `status`
- 经常作为 where 条件的字段。
- join 字段。

面试答法：

> 索引能提升查询速度，但会增加写入成本和存储成本。不是索引越多越好，要根据查询模式设计。

### B+Tree 为什么常用于数据库索引

B+Tree 特点：

- 多叉树，高度低。
- 叶子节点有序。
- 适合范围查询。
- 磁盘 IO 次数少。

面试答法：

> 数据库索引常用 B+Tree，因为它高度低、磁盘 IO 少，而且叶子节点有序，适合范围查询和排序。

### 联合索引和最左前缀

联合索引：

```sql
CREATE INDEX idx_user_status_time ON documents(user_id, status, created_at);
```

可以有效支持：

```sql
WHERE user_id = ?
WHERE user_id = ? AND status = ?
WHERE user_id = ? AND status = ? ORDER BY created_at
```

不一定有效支持：

```sql
WHERE status = ?
```

面试答法：

> 联合索引遵循最左前缀原则，查询条件要从索引最左列开始连续使用，才能更好命中索引。

### 索引失效常见情况

可能导致索引失效：

- 对索引字段使用函数。
- 左模糊匹配，如 `LIKE '%abc'`。
- 隐式类型转换。
- OR 条件使用不当。
- 不符合联合索引最左前缀。
- 数据量太小，优化器选择全表扫描。

例子：

```sql
WHERE DATE(created_at) = '2026-06-17'
```

可能不如：

```sql
WHERE created_at >= '2026-06-17'
  AND created_at < '2026-06-18'
```

### SQL 查询基础

常见语法：

```sql
SELECT id, title
FROM documents
WHERE user_id = 1
ORDER BY created_at DESC
LIMIT 20;
```

聚合：

```sql
SELECT status, COUNT(*)
FROM documents
GROUP BY status;
```

Join：

```sql
SELECT d.title, u.name
FROM documents d
JOIN users u ON d.user_id = u.id;
```

### JOIN

常见 JOIN：

- INNER JOIN：只返回两边都匹配的数据。
- LEFT JOIN：保留左表全部数据，右表没有则为 NULL。
- RIGHT JOIN：保留右表全部数据。

面试答法：

> INNER JOIN 取交集，LEFT JOIN 保留左表。实际业务里 LEFT JOIN 常用于“即使没有关联数据，也要保留主表记录”。

### 事务 ACID

事务四大特性：

- Atomicity 原子性：要么都成功，要么都失败。
- Consistency 一致性：事务前后数据满足约束。
- Isolation 隔离性：并发事务互不干扰。
- Durability 持久性：提交后数据不会丢。

面试答法：

> 事务保证一组操作作为整体执行，比如扣库存和创建订单必须一起成功或一起失败。

### 事务隔离级别

常见隔离级别：

- Read Uncommitted：可能脏读。
- Read Committed：避免脏读。
- Repeatable Read：避免不可重复读，MySQL 默认常见。
- Serializable：最高隔离，性能最低。

常见问题：

- 脏读：读到别人未提交的数据。
- 不可重复读：同一行两次读取结果不同。
- 幻读：同一范围两次查询行数不同。

面试答法：

> 隔离级别越高，一致性越强，但并发性能越低。工程里要在正确性和性能之间权衡。

### 慢查询优化

排查思路：

1. 看慢查询 SQL。
2. 用 `EXPLAIN` 看执行计划。
3. 检查是否走索引。
4. 检查扫描行数。
5. 检查 join 顺序和条件。
6. 优化索引或 SQL。
7. 必要时做分页、缓存、归档。

常见优化：

- 建合适索引。
- 避免 `SELECT *`。
- 避免深分页。
- 拆分复杂查询。
- 热点数据缓存到 Redis。

### EXPLAIN

`EXPLAIN` 用于查看 SQL 执行计划。

常看字段：

- type：访问类型。
- key：使用了哪个索引。
- rows：预计扫描行数。
- Extra：额外信息，如 Using filesort。

面试答法：

> SQL 慢时不能凭感觉改，先用 EXPLAIN 看是否走索引、扫描多少行、有没有 filesort 或临时表。

### 分页

普通分页：

```sql
SELECT *
FROM documents
ORDER BY id
LIMIT 20 OFFSET 10000;
```

问题：

> OFFSET 很大时，数据库仍然要跳过很多行，深分页会慢。

优化：

```sql
SELECT *
FROM documents
WHERE id > last_id
ORDER BY id
LIMIT 20;
```

这种叫游标分页或 keyset pagination。

### 数据库在 AI 应用中的表

常见表：

- users：用户。
- conversations：会话。
- messages：消息。
- documents：上传文档。
- chunks：文档切片 metadata。
- tasks：异步任务。
- evaluations：评估结果。
- feedback：用户反馈。
- api_usage：token 和成本统计。

面试答法：

> RAG 系统里向量库存 embedding，但 SQL 仍然很重要，用来存文档 metadata、权限、任务状态、会话记录和用户反馈。

### SQL 和向量库如何配合

常见设计：

```text
SQL documents 表：doc_id、owner、权限、标题、状态
SQL chunks 表：chunk_id、doc_id、页码、文本摘要
Vector DB：chunk_id、embedding、metadata
Object Storage：原始文件
```

查询时：

1. 根据用户权限确定可访问 doc_id。
2. 向量检索时加 metadata filter。
3. 召回 chunk_id。
4. 回 SQL 查标题、页码、来源等信息。

## 19. Redis / 缓存

Redis 是内存数据库，常用于缓存、限流、session、分布式锁、任务状态和排行榜。AI 应用里 Redis 很常见，因为 LLM 调用慢且贵，很多中间结果值得缓存。

### Redis 为什么快

主要原因：

- 数据在内存中。
- 单线程事件循环避免复杂锁竞争。
- I/O 多路复用。
- 数据结构实现高效。

面试答法：

> Redis 快主要因为基于内存和高效事件模型。单线程不代表慢，反而避免了多线程锁竞争。

### Redis 常用数据结构

String：

- 缓存普通值。
- 计数器。
- token 用量。

Hash：

- 存对象字段。
- 用户信息、任务状态。

List：

- 简单队列。
- 消息列表。

Set：

- 去重集合。
- 用户权限集合。

Sorted Set：

- 排行榜。
- 按分数排序的任务。

Bitmap / HyperLogLog：

- 统计类场景。

### 缓存基本模式

Cache Aside，旁路缓存：

```text
读请求 -> 先查 Redis
命中 -> 返回
未命中 -> 查数据库 -> 写 Redis -> 返回
```

写请求：

```text
先更新数据库，再删除缓存
```

面试答法：

> 常见缓存模式是 Cache Aside。读时先查缓存，未命中再查数据库并回填；写时通常更新数据库后删除缓存，避免旧数据残留。

### 过期时间 TTL

缓存通常要设置过期时间：

```bash
SET key value EX 3600
```

原因：

- 防止缓存无限增长。
- 避免长期返回旧数据。
- 自动清理不常用 key。

AI 应用例子：

- embedding 缓存可以较长。
- 用户会话缓存中等。
- 临时任务状态可设置短 TTL。

### 缓存穿透

缓存穿透是查询一个缓存和数据库都不存在的数据，导致请求每次都打到数据库。

解决：

- 缓存空值。
- 布隆过滤器。
- 参数校验。

例子：

> 恶意用户不断查不存在的 document_id，如果不缓存空结果，会一直打数据库。

### 缓存击穿

缓存击穿是某个热点 key 过期，瞬间大量请求打到数据库。

解决：

- 热点 key 不过期或逻辑过期。
- 加互斥锁，只让一个请求回源。
- 提前异步刷新。

### 缓存雪崩

缓存雪崩是大量 key 同时过期，导致数据库瞬间压力暴增。

解决：

- 过期时间加随机抖动。
- 分批过期。
- 多级缓存。
- 限流和降级。

### 缓存一致性

难点：

> 数据库和缓存是两个系统，很难保证强一致。

常见做法：

- 更新数据库后删除缓存。
- 缓存设置 TTL。
- 对强一致要求高的数据，不使用缓存或缩短缓存时间。

面试答法：

> 缓存通常追求最终一致。工程上常用“更新数据库后删除缓存 + TTL”来降低不一致风险。

### 分布式锁

Redis 可以用 `SET NX EX` 实现简单分布式锁：

```bash
SET lock_key request_id NX EX 10
```

含义：

- `NX`：不存在才设置。
- `EX`：设置过期时间，防止死锁。

释放锁时要确认 value 是自己的 request_id，避免误删别人的锁。

注意：

> 分布式锁要小心锁超时、误删锁、任务执行超过过期时间等问题。复杂场景可以考虑 Redlock 或更可靠的协调系统。

### Redis 限流

常见限流算法：

- 固定窗口。
- 滑动窗口。
- 令牌桶。
- 漏桶。

AI 应用场景：

- 用户每分钟最多请求多少次。
- 每天最多使用多少 tokens。
- 单个 tenant 最大并发数。

简单计数器：

```text
INCR user:123:minute:202606171230
EXPIRE 60
```

### Redis 做任务状态

长任务适合异步化：

```text
POST /tasks -> 返回 task_id
worker 后台处理
GET /tasks/{id} -> 查询状态
```

Redis 可存：

- pending
- running
- success
- failed
- progress
- error message

AI 场景：

- 文档解析。
- embedding 入库。
- 批量评估。
- 长 Agent 任务。

### Redis 做 LLM 缓存

可缓存：

- embedding 结果。
- query rewrite 结果。
- RAG 检索结果。
- rerank 结果。
- 高频问答结果。
- 用户 session 摘要。

缓存 key 设计：

```text
model_name + prompt_version + hash(input) + params
```

注意：

- 私有数据不能跨用户共享。
- prompt 或模型版本变化后缓存要失效。
- 结构化输出要缓存解析后的结果或原始结果都可以，但要明确。

### Redis 持久化

Redis 是内存数据库，但支持持久化。

RDB：

- 定期快照。
- 恢复快。
- 可能丢最近数据。

AOF：

- 记录写命令。
- 数据更完整。
- 文件可能更大。

面试答法：

> Redis 常用作缓存时，丢一点数据可以接受；如果存任务状态或重要数据，就要考虑持久化和恢复策略。

### Redis 淘汰策略

当内存满了，需要淘汰 key。

常见策略：

- noeviction：不淘汰，写入报错。
- allkeys-lru：所有 key 中淘汰最近最少使用。
- volatile-lru：只淘汰设置了过期时间的 key。
- allkeys-random：随机淘汰。

面试答法：

> Redis 作为缓存时常用 LRU 类策略，但关键业务状态不能随便被淘汰，要和普通缓存分开设计。

### Redis 常见工程坑

- 大 key 导致阻塞。
- 热 key 导致单点压力高。
- 缓存没有 TTL，内存爆。
- 把 Redis 当强一致数据库使用。
- 分布式锁没有过期时间。
- 删除锁时不校验 owner。
- 缓存 key 没有版本，模型/prompt 更新后还命中旧结果。

### 面试开放题：AI 应用里 Redis 怎么用

答题框架：

1. 缓存 embedding 和检索结果，降低成本。
2. 存 session 和临时任务状态。
3. 做用户级限流和 token quota。
4. 做分布式锁，避免重复处理同一文档。
5. 对热点问题缓存答案。
6. 设置 TTL、权限隔离和版本化 key。

## 20. 评估 Eval

### 为什么 LLM 应用需要评估

因为 LLM 输出不完全确定，改 prompt、换模型、调检索参数都可能影响结果，需要评估集做回归测试。

常见指标：

- 准确性
- 相关性
- 完整性
- 幻觉率
- 引用正确率
- 格式遵守率
- 延迟
- 成本

### RAG 评估

检索侧：

- Recall@k
- MRR
- Hit Rate
- 检索片段相关性

生成侧：

- 答案是否基于证据
- 是否回答完整
- 是否有幻觉
- 引用是否正确

面试答法：

> RAG 要拆开评估。先看检索有没有把答案证据召回，再看生成有没有基于证据正确回答。

### LLM-as-Judge

用 LLM 对答案质量打分。

优点：

- 自动化程度高。
- 适合开放式回答。

缺点：

- 评委模型也可能偏。
- 需要明确 rubric。
- 最好配合人工抽检。

## 21. 安全与合规

### 常见安全风险

- Prompt injection
- 数据泄露
- 越权检索
- 工具误调用
- 生成有害内容
- 用户上传恶意文件
- 日志里记录敏感信息

### 权限控制

RAG 场景尤其重要：

- 用户只能检索自己有权限的文档。
- metadata 中要有 owner、tenant、department 等字段。
- 检索时必须加权限 filter。
- 不能只在前端过滤。

面试答法：

> 企业 RAG 最容易出问题的是权限。向量检索时必须把权限过滤放在后端和数据库查询层，不能先全库召回再交给模型判断。

## 22. 性能与成本

### 影响延迟的因素

- 模型大小
- 输入 token 数
- 输出 token 数
- RAG 检索时间
- Rerank 时间
- 工具调用时间
- 网络延迟

优化方式：

- 缩短 prompt。
- 控制 max tokens。
- 使用流式输出。
- 缓存 embedding 和检索结果。
- 并行工具调用。
- 小模型处理简单任务，大模型处理复杂任务。

### 成本优化

- 减少无用上下文。
- 做 query 分类，简单问题走小模型。
- 缓存高频问题。
- RAG 只取必要 chunk。
- 控制重试次数。
- 对长文档先摘要再问答。

## 23. 前后端联调常见接口

### Chat 接口

请求：

```json
{
  "conversation_id": "xxx",
  "message": "用户问题",
  "stream": true
}
```

响应：

```json
{
  "answer": "模型回答",
  "sources": [
    {
      "doc_id": "doc-1",
      "title": "文档标题",
      "page": 3
    }
  ]
}
```

### 文件上传 + RAG 入库

流程：

1. 前端上传文件。
2. 后端保存原始文件。
3. 解析文本。
4. 切分 chunk。
5. 生成 embedding。
6. 写入向量数据库。
7. 返回入库状态。

### 任务状态接口

长任务不要让前端一直等同步返回。

常见设计：

- `POST /tasks` 创建任务。
- `GET /tasks/{id}` 查询状态。
- 状态包括 pending、running、success、failed。

## 24. 项目面试讲法

### RAG 项目怎么讲

推荐结构：

1. 背景：要解决什么业务问题。
2. 数据：文档来源、格式、规模。
3. 架构：解析、切分、embedding、向量库、检索、rerank、生成。
4. 难点：检索不准、chunk 切分、权限、幻觉、延迟。
5. 优化：hybrid search、rerank、引用、缓存、评估集。
6. 结果：准确率、延迟、用户反馈、成本。

一句话版本：

> 我做的是一个面向私有知识库的 RAG 问答系统，核心链路是文档解析入库、向量检索、重排序和基于证据生成回答。重点优化了 chunk 切分、检索召回和答案引用，降低幻觉并提升可追溯性。

### Agent 项目怎么讲

推荐结构：

1. Agent 目标：自动完成什么任务。
2. 工具：能调用哪些 API 或系统。
3. 决策流程：如何规划、执行、观察、停止。
4. 状态管理：任务状态、短期记忆、长期记忆。
5. 安全：权限、参数校验、人工确认。
6. 评估：成功率、平均步数、失败类型。

一句话版本：

> 我做的 Agent 不是简单聊天，而是让模型根据用户目标拆解任务、选择工具、执行并根据结果继续决策。工程上重点处理了工具 schema、参数校验、最大步数、错误恢复和关键操作确认。

## 25. 高频开放题

### 如何降低 LLM 幻觉？

答题框架：

- 让模型基于 RAG 证据回答。
- prompt 中要求不知道就说不知道。
- 输出引用来源。
- 对答案做事实一致性检查。
- 限制模型自由发挥。
- 对高风险场景引入人工审核。

### RAG 和 Fine-tuning 有什么区别？

答题框架：

- RAG 是推理时引入外部知识。
- Fine-tuning 是训练时调整模型行为。
- 知识更新和可追溯优先 RAG。
- 风格、格式、领域任务适配可考虑 Fine-tuning。

### Agent 和 Workflow 有什么区别？

答题框架：

- Workflow 是固定流程，步骤由程序写死。
- Agent 是动态决策，下一步由模型根据状态决定。
- Workflow 稳定可控，Agent 灵活但更难评估和约束。
- 生产中常用 workflow 包住 agent，让关键路径可控。

### 如何设计一个企业知识库问答系统？

答题框架：

1. 文档上传和权限管理。
2. 文档解析、切分、embedding 入库。
3. 查询时做权限过滤和向量检索。
4. rerank 后拼接上下文。
5. LLM 基于证据回答并给引用。
6. 记录日志、用户反馈和评估指标。
7. 优化延迟、成本和安全。

### 如何做 LLM 应用的灰度和回归测试？

答题框架：

- 建离线评估集。
- 固定 prompt 版本和模型版本。
- 比较新旧版本准确性、幻觉率、格式错误率、延迟和成本。
- 小流量灰度。
- 收集用户反馈。
- 出问题能快速回滚。

## 26. 面试速背清单

必须能讲清楚：

- Token、上下文窗口、temperature。
- 监督学习、无监督学习、过拟合、欠拟合、损失函数。
- Precision、Recall、F1、AUC、数据泄漏、类别不平衡。
- 逻辑回归、决策树、随机森林、GBDT、KMeans、PCA。
- 分词、词袋模型、TF-IDF、n-gram、HMM、CRF。
- Word2Vec、GloVe、RNN、LSTM、Seq2Seq、Attention。
- Transformer、self-attention、embedding。
- 预训练、SFT、RLHF、DPO、LoRA、QLoRA。
- 推理阶段的 prefill、decode、KV cache、量化。
- RAG 流程、chunk、向量检索、rerank。
- Prompt 结构化输出和 prompt injection。
- Agent、tool calling、ReAct、memory。
- SSE 流式输出、前端消息状态管理。
- 后端限流、缓存、日志、重试、权限。
- RAG vs Fine-tuning。
- 如何评估 LLM 应用。
- 如何降低幻觉。
- TCP/UDP 区别、三次握手、四次挥手。
- HTTP 方法、状态码、Header、HTTPS、CORS。
- SSE 和 WebSocket 区别。
- Docker 镜像、容器、Dockerfile、Compose、volume、端口映射。
- SQL 索引、事务、隔离级别、JOIN、EXPLAIN、慢查询优化。
- Redis 数据结构、缓存穿透/击穿/雪崩、分布式锁、限流。
