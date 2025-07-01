/** @file gnc-agent-system.h
 *  @brief Distributed Agentic Cognitive Grammar Kernelization System
 *  @author Generated for Z-GNN/gnucashyper
 *
 * This file implements the distributed network of agentic cognitive grammar
 * leveraging the division algebra hierarchy (ℝ, ℂ, ℍ, 𝕆) to instantiate 
 * meta-cognitive, hypergraph-powered accounting intelligence.
 *
 * Each agent is embodied in a recursive tensor field, operating as a 
 * specialized kernel with unique prime-factorized tensor shapes, orchestrated
 * through adaptive attention allocation (ECAN).
 */

#ifndef GNC_AGENT_SYSTEM_H
#define GNC_AGENT_SYSTEM_H

#include <glib.h>
#include <glib-object.h>
#include "qofinstance.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @name Division Algebra Level Constants */
/** @{ */
#define GNC_DIVISION_ALGEBRA_LEVEL_0_REAL       0  ///< ℝ - Real numbers
#define GNC_DIVISION_ALGEBRA_LEVEL_1_COMPLEX    1  ///< ℂ - Complex numbers  
#define GNC_DIVISION_ALGEBRA_LEVEL_2_QUATERNION 2  ///< ℍ - Quaternions
#define GNC_DIVISION_ALGEBRA_LEVEL_3_OCTONION   3  ///< 𝕆 - Octonions
#define GNC_DIVISION_ALGEBRA_MAX_LEVEL          3  ///< Maximum level (Hurwitz theorem)
/** @} */

/** @name Tensor Shape Constants */
/** @{ */
#define GNC_TENSOR_DIM_LEVEL_0  2   ///< [n_accounts, 2] real tensors
#define GNC_TENSOR_DIM_LEVEL_1  4   ///< [n_accounts, 4] complex tensors
#define GNC_TENSOR_DIM_LEVEL_2  8   ///< [n_accounts, 8] quaternion tensors  
#define GNC_TENSOR_DIM_LEVEL_3  16  ///< [n_accounts, 16] octonion tensors
/** @} */

/** @name Agent Role Types */
/** @{ */
typedef enum {
    GNC_AGENT_ROLE_MEMORY,      ///< Persistent state management
    GNC_AGENT_ROLE_TASK,        ///< Workflow orchestration
    GNC_AGENT_ROLE_ANALYTIC,    ///< Pattern recognition
    GNC_AGENT_ROLE_AUTONOMY     ///< Self-modification
} GncAgentRole;
/** @} */

/** @name Morphism Types */
/** @{ */
typedef enum {
    GNC_MORPHISM_PROPORTIONAL,  ///< Level 0: Linear scaling (real)
    GNC_MORPHISM_POLYNOMIAL,    ///< Level 1: Polynomial transforms (complex)
    GNC_MORPHISM_EXPONENTIAL,   ///< Level 2: Exponential series (quaternion)
    GNC_MORPHISM_ORDINAL        ///< Level 3: Transfinite operations (octonion)
} GncMorphismType;
/** @} */

/** Forward declarations */
typedef struct _GncAgent GncAgent;
typedef struct _GncAgentClass GncAgentClass;
typedef struct _GncTensorField GncTensorField;
typedef struct _GncECANController GncECANController;

/** @brief Core Agent Structure
 *
 * Each agent embodies a specialized cognitive kernel operating at a specific
 * division algebra level with unique tensor field representation.
 */
struct _GncAgent {
    QofInstance     parent;
    
    GncAgentRole    role;           ///< Agent's cognitive role
    gint            level;          ///< Division algebra level (0-3)
    gint            tensor_dims;    ///< Tensor dimensions for this level
    GncMorphismType morphism_type;  ///< Morphism transformation type
    
    GncTensorField  *tensor_field;  ///< GGML tensor field representation
    gpointer        morphism_data;  ///< Level-specific morphism parameters
    
    gdouble         attention_weight; ///< ECAN attention allocation
    gboolean        active;         ///< Agent activation state
    
    GHashTable      *hypernode_refs; ///< Hypergraph node references
    GList           *neighbor_agents; ///< Connected agents
};

/** @brief Tensor Field Structure
 *
 * Represents the GGML tensor field for an agent at a specific division algebra level.
 */
struct _GncTensorField {
    gint            level;          ///< Division algebra level
    gint            n_accounts;     ///< Number of accounts
    gint            tensor_dims;    ///< Tensor dimensions
    
    gpointer        ggml_context;   ///< GGML computation context
    gpointer        tensor_data;    ///< GGML tensor data pointer
    gsize           tensor_size;    ///< Size in bytes
    
    gdouble         *real_buffer;   ///< Real number buffer for computation
    gboolean        is_dirty;       ///< Needs recomputation flag
};

/** @brief ECAN Attention Controller
 *
 * Implements Economic Attention Networks for adaptive attention allocation
 * across all agents in the distributed system.
 */
struct _GncECANController {
    GObject         parent;
    
    GList           *agents;        ///< List of all agents
    gdouble         total_attention; ///< Total attention budget
    gdouble         attention_decay; ///< Attention decay rate
    
    GHashTable      *attention_map; ///< Agent -> attention mapping
    GTimer          *update_timer;  ///< Last update timestamp
};

/** @name Agent Management Functions */
/** @{ */

/**
 * Create a new agent with specified role and division algebra level
 * @param role Agent's cognitive role
 * @param level Division algebra level (0-3)
 * @param n_accounts Number of accounts for tensor sizing
 * @return New agent instance
 */
GncAgent* gnc_agent_new(GncAgentRole role, gint level, gint n_accounts);

/**
 * Initialize agent's tensor field for GGML computation
 * @param agent Target agent
 * @return TRUE if successful
 */
gboolean gnc_agent_init_tensor_field(GncAgent *agent);

/**
 * Execute agent's morphism transformation on tensor data
 * @param agent Target agent
 * @param input_data Input tensor data
 * @param output_data Output tensor data buffer
 * @return TRUE if successful
 */
gboolean gnc_agent_execute_morphism(GncAgent *agent, 
                                    const gdouble *input_data,
                                    gdouble *output_data);

/**
 * Update agent's hypergraph connections
 * @param agent Target agent
 * @param hypernode_id Hypergraph node identifier
 * @param connection_strength Connection weight
 */
void gnc_agent_update_hypernode(GncAgent *agent, 
                                const gchar *hypernode_id,
                                gdouble connection_strength);

/** @} */

/** @name ECAN Controller Functions */
/** @{ */

/**
 * Create new ECAN attention controller
 * @param total_attention Total attention budget
 * @return New ECAN controller
 */
GncECANController* gnc_ecan_controller_new(gdouble total_attention);

/**
 * Register agent with ECAN controller
 * @param controller ECAN controller
 * @param agent Agent to register
 */
void gnc_ecan_controller_register_agent(GncECANController *controller,
                                        GncAgent *agent);

/**
 * Update attention allocation across all agents
 * @param controller ECAN controller
 * @return TRUE if successful
 */
gboolean gnc_ecan_controller_update_attention(GncECANController *controller);

/**
 * Get current attention weight for agent
 * @param controller ECAN controller
 * @param agent Target agent
 * @return Current attention weight
 */
gdouble gnc_ecan_controller_get_attention(GncECANController *controller,
                                          GncAgent *agent);

/** @} */

/** @name Tensor Field Functions */
/** @{ */

/**
 * Create tensor field for specific division algebra level
 * @param level Division algebra level (0-3)
 * @param n_accounts Number of accounts
 * @return New tensor field
 */
GncTensorField* gnc_tensor_field_new(gint level, gint n_accounts);

/**
 * Perform Hopf projection for tensor field level
 * @param tensor_field Source tensor field
 * @param target_level Target projection level
 * @return Projected tensor data
 */
gdouble* gnc_tensor_field_hopf_project(GncTensorField *tensor_field,
                                       gint target_level);

/**
 * Execute division algebra operation on tensor
 * @param tensor_field Target tensor field
 * @param operation_type Operation to perform
 * @param operand_data Operand tensor data
 * @return Result tensor data
 */
gdouble* gnc_tensor_field_division_algebra_op(GncTensorField *tensor_field,
                                               const gchar *operation_type,
                                               const gdouble *operand_data);

/** @} */

/** @name Utility Functions */
/** @{ */

/**
 * Get tensor dimensions for division algebra level
 * @param level Division algebra level (0-3)
 * @return Tensor dimensions
 */
gint gnc_agent_get_tensor_dims_for_level(gint level);

/**
 * Get morphism type for division algebra level
 * @param level Division algebra level (0-3)
 * @return Morphism type
 */
GncMorphismType gnc_agent_get_morphism_for_level(gint level);

/**
 * Validate division algebra level
 * @param level Level to validate
 * @return TRUE if valid (0-3)
 */
gboolean gnc_agent_validate_level(gint level);

/** @} */

#ifdef __cplusplus
}
#endif

#endif /* GNC_AGENT_SYSTEM_H */