/** @file gnc-agent-types.h
 *  @brief Specific Agent Type Implementations
 *  @author Generated for Z-GNN/gnucashyper
 *
 * This file implements the four specific agent archetypes:
 * - MemoryAgent: Persistent state management (Level 0)
 * - TaskAgent: Workflow orchestration (Level 1)  
 * - AnalyticAgent: Pattern recognition (Level 2)
 * - AutonomyAgent: Self-modification (Level 3)
 */

#ifndef GNC_AGENT_TYPES_H
#define GNC_AGENT_TYPES_H

#include "gnc-agent-system.h"
#include "Account.h"
#include "Transaction.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @name MemoryAgent - Level 0 (Real Numbers) */
/** @{ */

/**
 * @brief MemoryAgent for persistent account state management
 * 
 * Operates at Level 0 with real number tensors [n_accounts, 2].
 * Provides persistent storage and retrieval of account states using
 * proportional morphisms for linear transformations.
 */
typedef struct _GncMemoryAgent {
    GncAgent        parent;
    
    GHashTable      *account_states;    ///< Account GUID -> tensor state mapping
    GHashTable      *transaction_log;   ///< Transaction history for replay
    gdouble         *balance_vector;    ///< Real-time balance vector
    
    gint            max_accounts;       ///< Maximum number of accounts
    gboolean        persistent_mode;    ///< Enable disk persistence
    gchar           *storage_path;      ///< Path for persistent storage
} GncMemoryAgent;

/**
 * Create new MemoryAgent for persistent state management
 * @param max_accounts Maximum number of accounts to track
 * @param storage_path Path for persistent storage (NULL for memory-only)
 * @return New MemoryAgent instance
 */
GncMemoryAgent* gnc_memory_agent_new(gint max_accounts, const gchar *storage_path);

/**
 * Store account state in memory agent
 * @param agent MemoryAgent instance
 * @param account Account to store
 * @param state_vector Account state as tensor [2] elements
 * @return TRUE if successful
 */
gboolean gnc_memory_agent_store_account_state(GncMemoryAgent *agent,
                                               Account *account,
                                               const gdouble *state_vector);

/**
 * Retrieve account state from memory agent
 * @param agent MemoryAgent instance
 * @param account Account to retrieve
 * @param state_vector Output buffer for state tensor [2] elements
 * @return TRUE if found and retrieved
 */
gboolean gnc_memory_agent_get_account_state(GncMemoryAgent *agent,
                                             Account *account,
                                             gdouble *state_vector);

/**
 * Log transaction for replay capability
 * @param agent MemoryAgent instance
 * @param transaction Transaction to log
 * @return TRUE if successful
 */
gboolean gnc_memory_agent_log_transaction(GncMemoryAgent *agent,
                                           Transaction *transaction);

/** @} */

/** @name TaskAgent - Level 1 (Complex Numbers) */
/** @{ */

/**
 * @brief TaskAgent for workflow orchestration and transaction cycles
 * 
 * Operates at Level 1 with complex number tensors [n_accounts, 4].
 * Manages transaction workflows and account morphisms using polynomial
 * transformations for complex state evolution.
 */
typedef struct _GncTaskAgent {
    GncAgent        parent;
    
    GQueue          *task_queue;        ///< Pending workflow tasks
    GHashTable      *workflow_states;   ///< Workflow ID -> state mapping
    gdouble         *flow_matrix;       ///< Transaction flow matrix [4x4]
    
    gint            max_workflows;      ///< Maximum concurrent workflows
    gdouble         completion_rate;    ///< Task completion rate
    GTimer          *cycle_timer;       ///< Workflow cycle timing
} GncTaskAgent;

/**
 * Workflow task structure for TaskAgent
 */
typedef struct _GncWorkflowTask {
    gchar           *task_id;           ///< Unique task identifier
    gchar           *workflow_type;     ///< Type of workflow
    GList           *accounts;          ///< Involved accounts
    gdouble         *complex_state;     ///< Complex state vector [4]
    gint            priority;           ///< Task priority (0-10)
    gboolean        completed;          ///< Completion status
} GncWorkflowTask;

/**
 * Create new TaskAgent for workflow orchestration
 * @param max_workflows Maximum number of concurrent workflows
 * @return New TaskAgent instance
 */
GncTaskAgent* gnc_task_agent_new(gint max_workflows);

/**
 * Schedule new workflow task
 * @param agent TaskAgent instance
 * @param task_id Unique task identifier
 * @param workflow_type Type of workflow to execute
 * @param accounts List of Account* involved in workflow
 * @param priority Task priority (0-10, higher = more important)
 * @return TRUE if scheduled successfully
 */
gboolean gnc_task_agent_schedule_workflow(GncTaskAgent *agent,
                                           const gchar *task_id,
                                           const gchar *workflow_type,
                                           GList *accounts,
                                           gint priority);

/**
 * Execute next workflow task in queue
 * @param agent TaskAgent instance
 * @return TRUE if task was executed
 */
gboolean gnc_task_agent_execute_next_task(GncTaskAgent *agent);

/**
 * Update workflow state using polynomial morphism
 * @param agent TaskAgent instance
 * @param workflow_id Workflow to update
 * @param input_state Input complex state [4]
 * @param output_state Output complex state [4]
 * @return TRUE if successful
 */
gboolean gnc_task_agent_update_workflow_state(GncTaskAgent *agent,
                                               const gchar *workflow_id,
                                               const gdouble *input_state,
                                               gdouble *output_state);

/** @} */

/** @name AnalyticAgent - Level 2 (Quaternions) */
/** @{ */

/**
 * @brief AnalyticAgent for pattern recognition and knowledge synthesis
 * 
 * Operates at Level 2 with quaternion tensors [n_accounts, 8].
 * Performs hypergraph pattern recognition and integrates with PLN/MOSES
 * for advanced analytics using exponential morphisms.
 */
typedef struct _GncAnalyticAgent {
    GncAgent        parent;
    
    GHashTable      *pattern_cache;     ///< Detected patterns cache
    GHashTable      *knowledge_graph;   ///< Knowledge graph nodes
    gdouble         *quaternion_space;  ///< Quaternion computation space
    
    gint            pattern_threshold;  ///< Minimum pattern strength
    gdouble         learning_rate;      ///< Pattern learning rate
    GList           *active_patterns;   ///< Currently active patterns
} GncAnalyticAgent;

/**
 * Pattern structure for AnalyticAgent
 */
typedef struct _GncPattern {
    gchar           *pattern_id;        ///< Unique pattern identifier
    gchar           *pattern_type;      ///< Type of pattern (flow, balance, etc.)
    gdouble         *quaternion_rep;    ///< Quaternion representation [8]
    gdouble         strength;           ///< Pattern strength (0.0-1.0)
    gint            frequency;          ///< Occurrence frequency
    GList           *related_accounts;  ///< Associated accounts
} GncPattern;

/**
 * Create new AnalyticAgent for pattern recognition
 * @param pattern_threshold Minimum pattern strength threshold
 * @return New AnalyticAgent instance
 */
GncAnalyticAgent* gnc_analytic_agent_new(gint pattern_threshold);

/**
 * Analyze account data for patterns
 * @param agent AnalyticAgent instance
 * @param accounts List of Account* to analyze
 * @param time_window Analysis time window in days
 * @return TRUE if analysis completed
 */
gboolean gnc_analytic_agent_analyze_patterns(GncAnalyticAgent *agent,
                                              GList *accounts,
                                              gint time_window);

/**
 * Detect specific pattern type in account data
 * @param agent AnalyticAgent instance
 * @param pattern_type Type of pattern to detect
 * @param account_data Account tensor data
 * @param pattern_result Output pattern structure
 * @return TRUE if pattern detected
 */
gboolean gnc_analytic_agent_detect_pattern(GncAnalyticAgent *agent,
                                            const gchar *pattern_type,
                                            const gdouble *account_data,
                                            GncPattern **pattern_result);

/**
 * Update knowledge graph with new insights
 * @param agent AnalyticAgent instance
 * @param node_id Knowledge graph node identifier
 * @param quaternion_data Quaternion knowledge representation [8]
 * @param confidence Confidence level (0.0-1.0)
 * @return TRUE if successful
 */
gboolean gnc_analytic_agent_update_knowledge(GncAnalyticAgent *agent,
                                              const gchar *node_id,
                                              const gdouble *quaternion_data,
                                              gdouble confidence);

/** @} */

/** @name AutonomyAgent - Level 3 (Octonions) */
/** @{ */

/**
 * @brief AutonomyAgent for meta-cognitive audit and self-modification
 * 
 * Operates at Level 3 with octonion tensors [n_accounts, 16].
 * Performs recursive morphism rewriting, policy deployment, and
 * meta-cognitive audit using ordinal transformations.
 */
typedef struct _GncAutonomyAgent {
    GncAgent        parent;
    
    GHashTable      *policy_rules;      ///< Active policy rules
    GHashTable      *morphism_history;  ///< Morphism evolution history
    gdouble         *octonion_meta;     ///< Meta-cognitive octonion space
    
    gint            recursion_depth;    ///< Current recursion depth
    gint            max_recursion;      ///< Maximum recursion depth
    gdouble         modification_rate;  ///< Self-modification rate
    GList           *audit_trail;       ///< Audit trail of modifications
} GncAutonomyAgent;

/**
 * Policy rule structure for AutonomyAgent
 */
typedef struct _GncPolicyRule {
    gchar           *rule_id;           ///< Unique rule identifier
    gchar           *rule_type;         ///< Type of policy rule
    gdouble         *octonion_params;   ///< Octonion parameters [16]
    gdouble         activation_level;   ///< Rule activation threshold
    gboolean        self_modifying;     ///< Can modify itself
    GList           *conditions;        ///< Activation conditions
} GncPolicyRule;

/**
 * Audit entry structure
 */
typedef struct _GncAuditEntry {
    gchar           *entry_id;          ///< Unique entry identifier
    gchar           *modification_type; ///< Type of modification made
    gdouble         *before_state;      ///< State before modification [16]
    gdouble         *after_state;       ///< State after modification [16]
    time_t          timestamp;          ///< Modification timestamp
    gdouble         confidence;         ///< Confidence in modification
} GncAuditEntry;

/**
 * Create new AutonomyAgent for meta-cognitive operations
 * @param max_recursion Maximum recursion depth for self-modification
 * @return New AutonomyAgent instance
 */
GncAutonomyAgent* gnc_autonomy_agent_new(gint max_recursion);

/**
 * Perform meta-cognitive audit of system state
 * @param agent AutonomyAgent instance
 * @param other_agents List of other agents to audit
 * @param audit_type Type of audit to perform
 * @return TRUE if audit completed
 */
gboolean gnc_autonomy_agent_perform_audit(GncAutonomyAgent *agent,
                                           GList *other_agents,
                                           const gchar *audit_type);

/**
 * Execute self-modification based on audit results
 * @param agent AutonomyAgent instance
 * @param modification_type Type of modification to perform
 * @param target_state Desired target state [16]
 * @return TRUE if modification successful
 */
gboolean gnc_autonomy_agent_self_modify(GncAutonomyAgent *agent,
                                         const gchar *modification_type,
                                         const gdouble *target_state);

/**
 * Deploy new policy rule to the system
 * @param agent AutonomyAgent instance
 * @param rule New policy rule to deploy
 * @param target_agents List of agents to apply rule to
 * @return TRUE if deployment successful
 */
gboolean gnc_autonomy_agent_deploy_policy(GncAutonomyAgent *agent,
                                           GncPolicyRule *rule,
                                           GList *target_agents);

/**
 * Perform recursive morphism trace and rewriting
 * @param agent AutonomyAgent instance
 * @param morphism_id Morphism to trace
 * @param recursion_level Current recursion level
 * @param rewrite_result Output rewritten morphism [16]
 * @return TRUE if successful
 */
gboolean gnc_autonomy_agent_recursive_morphism_trace(GncAutonomyAgent *agent,
                                                      const gchar *morphism_id,
                                                      gint recursion_level,
                                                      gdouble *rewrite_result);

/** @} */

/** @name Agent System Integration */
/** @{ */

/**
 * @brief Complete Agent System containing all 4 agent types
 */
typedef struct _GncAgentSystem {
    GncMemoryAgent      *memory_agent;      ///< Level 0: Persistent state
    GncTaskAgent        *task_agent;        ///< Level 1: Workflow orchestration
    GncAnalyticAgent    *analytic_agent;    ///< Level 2: Pattern recognition
    GncAutonomyAgent    *autonomy_agent;    ///< Level 3: Self-modification
    
    GncECANController   *ecan_controller;   ///< Attention allocation controller
    
    gint                n_accounts;         ///< Number of accounts in system
    gboolean            system_active;      ///< System activation state
    gdouble             cognitive_load;     ///< Current cognitive load
} GncAgentSystem;

/**
 * Create complete agent system with all 4 agent types
 * @param n_accounts Number of accounts to manage
 * @param storage_path Path for persistent storage (NULL for memory-only)
 * @return New complete agent system
 */
GncAgentSystem* gnc_agent_system_new(gint n_accounts, const gchar *storage_path);

/**
 * Initialize agent system and start cognitive loop
 * @param system Agent system to initialize
 * @return TRUE if successful
 */
gboolean gnc_agent_system_initialize(GncAgentSystem *system);

/**
 * Execute one cognitive cycle across all agents
 * @param system Agent system
 * @param accounts List of accounts to process
 * @return TRUE if cycle completed successfully
 */
gboolean gnc_agent_system_cognitive_cycle(GncAgentSystem *system,
                                           GList *accounts);

/**
 * Launch recursive meta-cognitive improvement loop
 * @param system Agent system
 * @param max_iterations Maximum number of improvement iterations
 * @return TRUE if loop completed
 */
gboolean gnc_agent_system_meta_cognitive_loop(GncAgentSystem *system,
                                               gint max_iterations);

/** @} */

#ifdef __cplusplus
}
#endif

#endif /* GNC_AGENT_TYPES_H */