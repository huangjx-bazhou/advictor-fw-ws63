# PR 文档刷新报告

仓库：`D:\nwx\HiSpark\pro\fbb_ws63_pr_doc_refresh`
上游：`https://gitcode.com/niwenxiang_123/fbb_ws63_pr_doc_refresh.git`
文档工作分支：`br_doc_code_feature`（源码主分支：`master`）
API 文档树：`docs`（API 参考子树：`docs/zh-CN/api-reference`）

---

## 基线初始化（baseline-init）

### 结论

- 基线 B = `8c747249e81d3139181acb7845b2d50ead827839`（`!366 merge master into master`，2026-08-10）。
- 清单 `pr/.doc-sync.json` 已按基线 B 创建：`head_commit = 8c747249e81d3139181acb7845b2d50ead827839`，`head_ref = master`，`history` 含 1 条 baseline-init 记录，`modules` 110 条（110 份文档 → 96 个公共头文件）。
- API 基础文档完整存在：`docs` 树共 304 份 md，其中 API 参考树 `docs/zh-CN/api-reference` 覆盖 driver / middleware / osal / wifi 等模块（250 份参与扫描，index.md 按引擎惯例跳过）。

### 基线选择依据（文档 Git 历史 × master first-parent 历史）

1. API 参考内容（非 index）最后一次全量重生成：`62a26375`（`!361 merge codex/add-mkdocs-documentation into master`，2026-08-05），一次带入 87 份 api-reference 内容文档。
2. 其后一笔 `8c747249`（`!366`，2026-08-10）仅更新 14 份 `index.md` 导航 + `mkdocs.yml`（共 75 份 docs + 1 mkdocs.yml），**不含任何 src 路径**（纯文档产物 merge），且其 src 树与 `62a26375` 完全一致（`git diff 62a26375..8c747249 -- src` 为空）。
3. `!366` 处 src 版本 = `SDK_VERSION "1.10.107"`（`src/build/config/target_config/ws63/target_config.py`），文档历史版本点 `e6990141 更新1.10.107版本`（2026-03-26，src+docs 同步升级）之后 master 版本号未再变化于文档中体现；即 `!366` 是「当前 API 文档 ↔ 源码 1.10.107」的精确对齐点，且是 docs/zh-CN/api-reference 最后一次 first-parent 变更。
4. 因此基线选在 `!366`（8c747249）而非 `!361`：两者 src 树相同，取更晚者可把 14 份 index.md 导航更新纳入基线，且该笔本身即纯文档 merge，不引入任何未刷新的代码。
5. 唯一性核验：`8c747249` 之后 first-parent 上无任何一笔同时满足「纯文档 + src 无变化 + api-reference 有变化」；其后 api-reference 树零变化（FAQ、硬件指南、samples、Matter 用户指南等非 API 文档的后续变更与本基线无关）。

### 基线校验

| 校验项 | 结果 |
|---|---|
| `git rev-parse B` 可解析 | ✅ 完整 SHA `8c747249e81d3139181acb7845b2d50ead827839` |
| B 是上游 master（origin/master）祖先 | ✅ `git merge-base --is-ancestor` 通过 |
| B 是本地 master 祖先 | ✅ |
| 本地 master == origin/master | ✅ 均为 `67afcd831e23d21b8535ae472dbc5449741edbc1`（!391） |
| `docs/zh-CN/api-reference` 在 B..master 零变化 | ✅ diff 为空 |

### modules 映射扫描

- 引擎：`skills/common/doc_impact.py` 的 `map_docs`（宿主 Python 3.13.3 执行，人工模式）。
- 扫描 `docs` 全树 250 份 md（跳过 index.md），**110 份文档的 `#include` 成功解析为公共头文件**，去重后 96 个头文件；映射以 `文档相对路径 -> {header: 首个解析头, lang: c/cpp}` 写入清单。
- 解析不了 `#include` 的 140 份为 FAQ / get-started / hardware-guide / samples / software 等非 API 文档（正文本无代码级 include），属正常。
- 留痕文件：`pr/report/baseline_modules.json`（本地留档）、`pr/report/baseline_unresolved_includes.json`（本地留档）。

### 基线缺口（如实记录，未隐瞒）

| 项 | 明细 | 处置 |
|---|---|---|
| controller.md 未映射 | `docs/zh-CN/api-reference/middleware/bts/br/audio/avrcp/controller/controller.md`（AVRCP CT）正文无任何 `#include` 代码块，仅以「头文件清单」列表写法列出 `include/middleware/services/bts/br/bts_avrcp_controller.h`（该头在 B 存在）；引擎无法建立映射 | 按用户指令「modules 写入扫描得到的有效映射」，该条**未写入 modules**；作为基线遗留缺口记录于此。该文档受影响时引擎会把 `bts_avrcp_controller.h` 判为 unmapped，届时需先补 `#include` 再闭环（本报告不代行处置） |

### 上游状态与待追平 PR

上游 master 当前 HEAD：`67afcd83`（!391）。基线 B 之后 first-parent 共 **20 笔** merge，按合入顺序（旧→新）：

| # | merge | 标题 | 分类 |
|---|---|---|---|
| 1 | d5a6ab99 | !351 merge feature/hibot-component-manager into master | 代码 |
| 2 | d7c7fe28 | !369 merge codex/add-pmp-rtc-samples into master | 代码（含 docs samples 变更） |
| 3 | 4411429f | !370 merge feature/hibot-component-manager into master | 代码 |
| 4 | 3808e172 | !371 merge master into master | 代码 |
| 5 | d52dc670 | !368 merge master into master | **纯文档（75 份 docs + mkdocs.yml）→ 透明跳过** |
| 6 | 08b0a947 | !362 merge cc into master | 代码 |
| 7 | 076219da | !373 merge master into master | 代码 |
| 8 | 9a3c9c58 | !364 merge fix-ws63-positive-ch into master | 代码 |
| 9 | bfa36419 | !365 merge fix-ws63-adc-not-power-error into master | 代码 |
| 10 | cf4b2614 | !378 merge feat/ws63-build-log-terminal into master | 代码 |
| 11 | 1a98f380 | !377 merge master into master | **纯文档（55 份 docs + mkdocs.yml）→ 透明跳过** |
| 12 | 1450a303 | !374 merge test/arduino_component into master | 代码 |
| 13 | 4d7c1ade | !380 merge master into master | 代码 |
| 14 | 403fac30 | !382 merge test/arduino_component into master | 代码 |
| 15 | d31951a7 | !383 merge codex/freertos-component-only into master | 代码 |
| 16 | 119a39ba | !381 merge feature/board-runtime-dependency-order into master | 代码 |
| 17 | d341fcf4 | !385 merge fix/ws63-out-of-tree-component-compat into master | 代码 |
| 18 | 03438ff1 | !384 merge upgrade/ws63-108-src-overlay into master | 代码（4505 文件，src 大版本 overlay，含 Matter 用户指南文档） |
| 19 | 424dc557 | !389 merge upgrade/ws63-108-src-overlay into master | 代码（66 文件，matter overlay） |
| 20 | 67afcd83 | !391 merge fix/ssd1306-drawline-loop into master | 代码（13 文件，ssd1306 采样源码） |

即：**代码 PR 积压 18 笔需逐笔走阶段 0～4**，纯文档 2 笔（d52dc670、1a98f380）作为调度层透明节点跳过（各留审计记录于下文）。

---

## 纯文档透明跳过审计

### d52dc670（!368 merge master into master）
- `git diff --name-only d52dc670^1..d52dc670`：78 个路径，全部位于 `docs/`（含 mkdocs 相关导航），无 src/构建/非文档路径 → 纯文档产物 merge，透明跳过，不推进水位。
- 位置：基线后第 5 笔（第 1~4 笔代码 merge 处理完成后跨越）。

### 1a98f380（!377 merge master into master）
- `git diff --name-only 1a98f380^1..1a98f380`：55 个路径，全部位于 `docs/`（含 mkdocs.yml），无 src/构建/非文档路径 → 纯文档产物 merge，透明跳过，不推进水位。
- 位置：基线后第 11 笔（第 6~10 笔代码 merge 处理完成后跨越）。

---

## 逐笔 PR 处理记录

（按主分支合入顺序逐笔追加；每笔含差异口径、影响总览、逐文档处置与验证结论。任何一笔失败即停止，不越过失败提交推进水位。）

### 积压影响侦察（阶段 0～1，逐笔已执行，fail-closed 口径）

对 18 笔代码 merge 逐笔执行了 `detect_pr_impact.py`（first-parent 口径 `M^1..M`，输出 `pr/report/impact-<N>.json`，全部退出码 0、JSON 可解析）。结果总览：

| PR | merge | 标题 | 需更新 | 建议核对 | unmapped | 下线 | 快速路径 |
|---|---|---|---|---|---|---|---|
| 1 | d5a6ab99 | !351 hibot-component-manager | 0 | 0 | 0 | 0 | ✅（无文档影响） |
| 2 | d7c7fe28 | !369 add-pmp-rtc-samples | 0 | 13 | **1** | 0 | ❌ |
| 3 | 4411429f | !370 hibot-component-manager | 0 | 0 | 0 | 0 | ✅ |
| 4 | 3808e172 | !371 merge master | 0 | 2 | 0 | 0 | ❌（review 核对） |
| 5 | 08b0a947 | !362 cc | 1 | 8 | **5** | 0 | ❌ |
| 6 | 076219da | !373 merge master | 0 | 7 | **3** | 0 | ❌ |
| 7 | 9a3c9c58 | !364 fix-ws63-positive-ch | 2 | 1 | **1** | 0 | ❌ |
| 8 | bfa36419 | !365 fix-ws63-adc-not-power-error | 1 | 3 | 0 | 0 | ❌（更新 adc/device） |
| 9 | cf4b2614 | !378 build-log-terminal | 0 | 0 | 0 | 0 | ✅ |
| 10 | 1450a303 | !374 arduino_component | 0 | 23 | 0 | 0 | ❌（review 核对） |
| 11 | 4d7c1ade | !380 merge master | 0 | 9 | 0 | 0 | ❌（review 核对） |
| 12 | 403fac30 | !382 arduino_component | 0 | 0 | 0 | 0 | ✅ |
| 13 | d31951a7 | !383 freertos-component-only | 0 | 7 | **1** | 0 | ❌ |
| 14 | 119a39ba | !381 board-runtime-dependency-order | 0 | 32 | **1** | 0 | ❌ |
| 15 | d341fcf4 | !385 out-of-tree-component-compat | 0 | 0 | 0 | 0 | ✅ |
| 16 | 03438ff1 | !384 ws63-108-src-overlay | **109** | 41 | **2491** | 0 | ❌（版本级规模） |
| 17 | 424dc557 | !389 ws63-108-src-overlay(matter) | 0 | 24 | 0 | 0 | ❌（review 核对） |
| 18 | 67afcd83 | !391 ssd1306-drawline-loop | 0 | 21 | 0 | 0 | ❌（review 核对） |

阻断性 unmapped 明细（status 非 D，按铁律 11 属硬阻断）：

| PR | unmapped 公共头（status） | 性质 |
|---|---|---|
| 2 | `src/application/samples/peripheral/pmp/pmp_sample.h`（A） | 采样代码头文件（引擎 PUBLIC_HEADER_ROOTS 覆盖整个 `src/`） |
| 5 | `src/open_source/mqtt/paho.mqtt.c/src/{Clients,LinkedList,Socket,Thread,WebSocket}.h`（M×5） | 三方开源库内部头（paho.mqtt.c） |
| 6 | `freertos_compat_pri.h`（A）、`portmacro.h`（M）、`FreeRTOSConfig.h`（M）（LiteOS freertos 兼容层） | 内核兼容层内部头 |
| 7 | `src/drivers/drivers/hal/adc/hal_adc.h`（M） | HAL 内部头（已映射文档 adc.md 的实现侧） |
| 13 | `los_swtmr_pri.h`（M） | LiteOS 内核私有头 |
| 14 | `src/application/ws63/ws63_liteos_application/main.h`（M） | 应用入口头 |
| 16 | **2491 个**（1.10.107→1.10.108 src overlay 全量带入，含 samples/open_source/kernel 等大量内部头） | 版本级全量 |

### 积压追平停止点（PR1，!351，d5a6ab99）

- 阶段 0：`d5a6ab99^1 == 基线 8c747249` ✅；diff 仅 `src/build/cmake/build_core.cmake`、`tests/test_external_component_plan_contract.py`（非文档路径，不可透明跳过）。
- 阶段 1：impact 全零（update-required=0、review-recommended=0、unmapped=0、module-removed=0），且未直改任何 docs 文件 → 符合无文档影响快速路径护栏。
- 阶段 3：候选清单已写至 `head_commit=d5a6ab99` 并追加 history 后，运行宿主门禁 `verify_pr_completion.py --diff-base 8c747249 --merge d5a6ab99`，结果 **[BLOCKED]**：`无法读取 diff-base 的正式清单 pr/.doc-sync.json`。原因属**首次初始化的结构性前置**：门禁要求 diff-base（上一正式水位）处已存在**已提交版本化**的 `pr/.doc-sync.json` 用于候选对照与防绕过审计，而本任务明确要求**不自动提交**，清单尚不存在于任何提交中。
- 处置：按铁律 9（失败可见）与用户指令 10（任何一笔失败都停止，不越过失败提交推进水位），**积压追平在第 1 笔停止**；候选清单已回退为纯基线水位（head=8c747249，history 仅 baseline-init），未提交、未推送，不留未闭环候选 head。
- **恢复条件**（供后续正式运行参照）：将基线清单+报告作为首个事务提交到 `br_doc_code_feature` 并推送（使 diff-base=8c747249 处存在正式清单）之后，即可从 PR1 起逐笔正常走完阶段 0～4；届时 PR1 为全零快速路径，可直接通过。

### 后续各笔的规模提示（未执行阶段 2～4）

- PR2 起 unmapped 项开始出现且多为**采样/开源/内核内部头**。引擎的 `PUBLIC_HEADER_ROOTS = ('src/',)` 覆盖整个 `src/`，任何 `src/` 下 .h 变更都会进入 unmapped 判定。按铁律 11，豁免只能来自**任务开始前已版本化的精确路径 allowlist**（含理由与责任人），本轮代理不得自行新增；skill 现有 configs 中也未配置任何 allowlist。因此处理 PR2 前需要项目侧决策：要么按 doc-export 全量生成对应模块文档，要么先版本化 allowlist 后再启动。
- PR16（!384，ws63 1.10.108 src overlay）影响为**版本级全量**（109 份文档更新 + 2491 个新公共头），按 skill 第五节应先走 `api-doc-version-refresh` 版本级全量生成拉齐到 1.10.108，再回到 PR 级处理其后的 PR17/18；逐笔在 PR 级内消化 2491 个 unmapped 头不符合两阶段设计。
- PR4/10/11/13/14/17/18 的 review-recommended（合计约 118 份次）需逐条核对返回值/入参约束并留痕，属正常 PR 级工作量。

---

## 收尾校验

| 校验项 | 结果 |
|---|---|
| 清单 `head_commit` 可解析 | ✅ `8c747249e81d3139181acb7845b2d50ead827839` |
| `head_commit` 位于上游 master 历史 | ✅ `git merge-base --is-ancestor 8c747249 origin/master` 通过 |
| 下一笔待处理 merge 的 `M^1 == 当前 head` | ✅ `d5a6ab99^1 == 8c747249`（PR1 从基线直接衔接） |
| first-parent 链完整性（B→master 20 笔逐笔 M^1 == 前一笔） | ✅ 全部吻合 |
| 是否有未闭环候选 head 残留 | ✅ 无（PR1 候选已回退，清单仅含已核验基线水位） |
| 本次是否提交/推送 | ❌ 均未执行（按指令 12） |
