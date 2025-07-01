/** @file gnc-agent-system.c
 *  @brief Implementation of Distributed Agentic Cognitive Grammar System
 *  @author Generated for Z-GNN/gnucashyper
 */

#include "gnc-agent-system.h"
#include <math.h>
#include <string.h>
#include <stdlib.h>

/** @name Static Data */
/** @{ */

/** Division algebra level tensor dimensions lookup table */
static const gint TENSOR_DIMS[4] = {
    GNC_TENSOR_DIM_LEVEL_0,  // Level 0: 2 (real)
    GNC_TENSOR_DIM_LEVEL_1,  // Level 1: 4 (complex)
    GNC_TENSOR_DIM_LEVEL_2,  // Level 2: 8 (quaternion)  
    GNC_TENSOR_DIM_LEVEL_3   // Level 3: 16 (octonion)
};

/** Morphism type lookup for each level */
static const GncMorphismType LEVEL_MORPHISMS[4] = {
    GNC_MORPHISM_PROPORTIONAL,  // Level 0: Real proportional
    GNC_MORPHISM_POLYNOMIAL,    // Level 1: Complex polynomial
    GNC_MORPHISM_EXPONENTIAL,   // Level 2: Quaternion exponential
    GNC_MORPHISM_ORDINAL        // Level 3: Octonion ordinal
};

/** @} */

/** @name Agent Implementation */
/** @{ */

GncAgent* gnc_agent_new(GncAgentRole role, gint level, gint n_accounts)
{
    g_return_val_if_fail(gnc_agent_validate_level(level), NULL);
    g_return_val_if_fail(n_accounts > 0, NULL);
    
    GncAgent *agent = g_new0(GncAgent, 1);
    
    // Initialize QofInstance parent
    qof_instance_init_data(&agent->parent, 
                          g_strdup_printf("agent-%d-%d", role, level),
                          NULL);
    
    agent->role = role;
    agent->level = level;
    agent->tensor_dims = gnc_agent_get_tensor_dims_for_level(level);
    agent->morphism_type = gnc_agent_get_morphism_for_level(level);
    
    agent->tensor_field = gnc_tensor_field_new(level, n_accounts);
    agent->morphism_data = NULL;
    
    agent->attention_weight = 1.0 / (level + 1); // Higher levels get less initial attention
    agent->active = TRUE;
    
    agent->hypernode_refs = g_hash_table_new_full(g_str_hash, g_str_equal,
                                                  g_free, NULL);
    agent->neighbor_agents = NULL;
    
    g_debug("Created agent: role=%d, level=%d, dims=%d, morphism=%d",
            role, level, agent->tensor_dims, agent->morphism_type);
    
    return agent;
}

gboolean gnc_agent_init_tensor_field(GncAgent *agent)
{
    g_return_val_if_fail(agent != NULL, FALSE);
    g_return_val_if_fail(agent->tensor_field != NULL, FALSE);
    
    GncTensorField *field = agent->tensor_field;
    
    // For now, we'll use simple malloc instead of GGML until we integrate it
    // Calculate total tensor size
    gsize total_size = field->n_accounts * field->tensor_dims * sizeof(gdouble);
    
    field->real_buffer = g_malloc0(total_size);
    field->tensor_size = total_size;
    field->is_dirty = FALSE;
    
    // Initialize with identity-like values based on division algebra level
    for (gint i = 0; i < field->n_accounts; i++) {
        gdouble *account_tensor = &field->real_buffer[i * field->tensor_dims];
        
        switch (field->level) {
            case GNC_DIVISION_ALGEBRA_LEVEL_0_REAL:
                // Real: [1.0, 0.0] (real + imaginary part)
                account_tensor[0] = 1.0;
                account_tensor[1] = 0.0;
                break;
                
            case GNC_DIVISION_ALGEBRA_LEVEL_1_COMPLEX:
                // Complex: [1.0, 0.0, 0.0, 0.0] (real, imag, 0, 0)
                account_tensor[0] = 1.0;
                account_tensor[1] = 0.0;
                account_tensor[2] = 0.0;
                account_tensor[3] = 0.0;
                break;
                
            case GNC_DIVISION_ALGEBRA_LEVEL_2_QUATERNION:
                // Quaternion: [1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0]
                account_tensor[0] = 1.0; // real part
                for (gint j = 1; j < 8; j++) {
                    account_tensor[j] = 0.0;
                }
                break;
                
            case GNC_DIVISION_ALGEBRA_LEVEL_3_OCTONION:
                // Octonion: [1.0, 0.0, ...] (16 components)
                account_tensor[0] = 1.0; // real part
                for (gint j = 1; j < 16; j++) {
                    account_tensor[j] = 0.0;
                }
                break;
        }
    }
    
    g_debug("Initialized tensor field for agent level %d with %d accounts",
            field->level, field->n_accounts);
    
    return TRUE;
}

gboolean gnc_agent_execute_morphism(GncAgent *agent, 
                                    const gdouble *input_data,
                                    gdouble *output_data)
{
    g_return_val_if_fail(agent != NULL, FALSE);
    g_return_val_if_fail(input_data != NULL, FALSE);
    g_return_val_if_fail(output_data != NULL, FALSE);
    
    GncTensorField *field = agent->tensor_field;
    gint n_elements = field->n_accounts * field->tensor_dims;
    
    switch (agent->morphism_type) {
        case GNC_MORPHISM_PROPORTIONAL:
            // Level 0: Linear scaling (proportional morphism)
            {
                gdouble scale_factor = 1.0 + 0.1 * sin(g_timer_elapsed(NULL, NULL));
                for (gint i = 0; i < n_elements; i++) {
                    output_data[i] = input_data[i] * scale_factor;
                }
            }
            break;
            
        case GNC_MORPHISM_POLYNOMIAL:
            // Level 1: Polynomial transformation (degree 2)
            {
                for (gint i = 0; i < n_elements; i++) {
                    gdouble x = input_data[i];
                    output_data[i] = x + 0.1 * x * x; // f(x) = x + 0.1*x^2
                }
            }
            break;
            
        case GNC_MORPHISM_EXPONENTIAL:
            // Level 2: Exponential series transformation
            {
                for (gint i = 0; i < n_elements; i++) {
                    gdouble x = input_data[i];
                    // Taylor series approximation: exp(0.1*x) ≈ 1 + 0.1*x + 0.005*x^2
                    output_data[i] = 1.0 + 0.1 * x + 0.005 * x * x;
                }
            }
            break;
            
        case GNC_MORPHISM_ORDINAL:
            // Level 3: Ordinal (transfinite) transformation
            {
                for (gint i = 0; i < n_elements; i++) {
                    gdouble x = input_data[i];
                    // Non-associative operation mimicking octonion behavior
                    output_data[i] = x + 0.01 * sin(x) * cos(x * 1.618); // Golden ratio factor
                }
            }
            break;
    }
    
    g_debug("Executed morphism type %d for agent level %d",
            agent->morphism_type, agent->level);
    
    return TRUE;
}

void gnc_agent_update_hypernode(GncAgent *agent, 
                                const gchar *hypernode_id,
                                gdouble connection_strength)
{
    g_return_if_fail(agent != NULL);
    g_return_if_fail(hypernode_id != NULL);
    
    g_hash_table_insert(agent->hypernode_refs,
                        g_strdup(hypernode_id),
                        GDOUBLE_TO_POINTER(connection_strength));
    
    g_debug("Updated hypernode %s for agent level %d with strength %f",
            hypernode_id, agent->level, connection_strength);
}

/** @} */

/** @name ECAN Controller Implementation */
/** @{ */

GncECANController* gnc_ecan_controller_new(gdouble total_attention)
{
    g_return_val_if_fail(total_attention > 0.0, NULL);
    
    GncECANController *controller = g_new0(GncECANController, 1);
    
    controller->agents = NULL;
    controller->total_attention = total_attention;
    controller->attention_decay = 0.01; // 1% decay per update
    
    controller->attention_map = g_hash_table_new(g_direct_hash, g_direct_equal);
    controller->update_timer = g_timer_new();
    
    g_debug("Created ECAN controller with total attention budget %f",
            total_attention);
    
    return controller;
}

void gnc_ecan_controller_register_agent(GncECANController *controller,
                                        GncAgent *agent)
{
    g_return_if_fail(controller != NULL);
    g_return_if_fail(agent != NULL);
    
    controller->agents = g_list_append(controller->agents, agent);
    
    // Initial attention allocation based on agent level (higher levels get less)
    gdouble initial_attention = controller->total_attention / 
                                (g_list_length(controller->agents) * (agent->level + 1));
    
    g_hash_table_insert(controller->attention_map,
                        agent,
                        GDOUBLE_TO_POINTER(initial_attention));
    
    g_debug("Registered agent level %d with ECAN controller, initial attention %f",
            agent->level, initial_attention);
}

gboolean gnc_ecan_controller_update_attention(GncECANController *controller)
{
    g_return_val_if_fail(controller != NULL, FALSE);
    
    gdouble elapsed = g_timer_elapsed(controller->update_timer, NULL);
    g_timer_start(controller->update_timer);
    
    gdouble total_allocated = 0.0;
    gint n_agents = g_list_length(controller->agents);
    
    if (n_agents == 0) {
        return TRUE;
    }
    
    // Apply decay and competitive allocation
    for (GList *iter = controller->agents; iter != NULL; iter = iter->next) {
        GncAgent *agent = (GncAgent *)iter->data;
        
        gdouble current_attention = GPOINTER_TO_DOUBLE(
            g_hash_table_lookup(controller->attention_map, agent));
        
        // Decay attention
        current_attention *= (1.0 - controller->attention_decay * elapsed);
        
        // Boost attention based on agent activity and importance
        if (agent->active) {
            gdouble importance_factor = 1.0 / (agent->level + 1); // Higher levels are more specialized
            gdouble activity_boost = 0.1 * importance_factor;
            current_attention += activity_boost;
        }
        
        total_allocated += current_attention;
        
        g_hash_table_insert(controller->attention_map,
                            agent,
                            GDOUBLE_TO_POINTER(current_attention));
    }
    
    // Normalize to total attention budget
    if (total_allocated > 0.0) {
        gdouble normalization_factor = controller->total_attention / total_allocated;
        
        for (GList *iter = controller->agents; iter != NULL; iter = iter->next) {
            GncAgent *agent = (GncAgent *)iter->data;
            
            gdouble current_attention = GPOINTER_TO_DOUBLE(
                g_hash_table_lookup(controller->attention_map, agent));
            
            current_attention *= normalization_factor;
            agent->attention_weight = current_attention;
            
            g_hash_table_insert(controller->attention_map,
                                agent,
                                GDOUBLE_TO_POINTER(current_attention));
        }
    }
    
    g_debug("Updated attention allocation for %d agents, total budget %f",
            n_agents, controller->total_attention);
    
    return TRUE;
}

gdouble gnc_ecan_controller_get_attention(GncECANController *controller,
                                          GncAgent *agent)
{
    g_return_val_if_fail(controller != NULL, 0.0);
    g_return_val_if_fail(agent != NULL, 0.0);
    
    gpointer value = g_hash_table_lookup(controller->attention_map, agent);
    return value ? GPOINTER_TO_DOUBLE(value) : 0.0;
}

/** @} */

/** @name Tensor Field Implementation */
/** @{ */

GncTensorField* gnc_tensor_field_new(gint level, gint n_accounts)
{
    g_return_val_if_fail(gnc_agent_validate_level(level), NULL);
    g_return_val_if_fail(n_accounts > 0, NULL);
    
    GncTensorField *field = g_new0(GncTensorField, 1);
    
    field->level = level;
    field->n_accounts = n_accounts;
    field->tensor_dims = gnc_agent_get_tensor_dims_for_level(level);
    
    field->ggml_context = NULL; // Will be initialized when GGML is integrated
    field->tensor_data = NULL;
    field->tensor_size = 0;
    
    field->real_buffer = NULL;
    field->is_dirty = TRUE;
    
    g_debug("Created tensor field: level=%d, accounts=%d, dims=%d",
            level, n_accounts, field->tensor_dims);
    
    return field;
}

gdouble* gnc_tensor_field_hopf_project(GncTensorField *tensor_field,
                                       gint target_level)
{
    g_return_val_if_fail(tensor_field != NULL, NULL);
    g_return_val_if_fail(gnc_agent_validate_level(target_level), NULL);
    g_return_val_if_fail(target_level <= tensor_field->level, NULL);
    
    gint source_dims = tensor_field->tensor_dims;
    gint target_dims = gnc_agent_get_tensor_dims_for_level(target_level);
    gint n_accounts = tensor_field->n_accounts;
    
    gdouble *projected_data = g_malloc0(n_accounts * target_dims * sizeof(gdouble));
    
    // Hopf projection: map from higher dimensional sphere to lower dimensional sphere
    for (gint i = 0; i < n_accounts; i++) {
        gdouble *source_tensor = &tensor_field->real_buffer[i * source_dims];
        gdouble *target_tensor = &projected_data[i * target_dims];
        
        // Simple projection: take first target_dims components and normalize
        gdouble norm_sq = 0.0;
        for (gint j = 0; j < target_dims && j < source_dims; j++) {
            target_tensor[j] = source_tensor[j];
            norm_sq += target_tensor[j] * target_tensor[j];
        }
        
        // Normalize to unit sphere
        if (norm_sq > 0.0) {
            gdouble norm = sqrt(norm_sq);
            for (gint j = 0; j < target_dims; j++) {
                target_tensor[j] /= norm;
            }
        }
    }
    
    g_debug("Hopf projected tensor field from level %d to level %d",
            tensor_field->level, target_level);
    
    return projected_data;
}

gdouble* gnc_tensor_field_division_algebra_op(GncTensorField *tensor_field,
                                               const gchar *operation_type,
                                               const gdouble *operand_data)
{
    g_return_val_if_fail(tensor_field != NULL, NULL);
    g_return_val_if_fail(operation_type != NULL, NULL);
    g_return_val_if_fail(operand_data != NULL, NULL);
    
    gint n_elements = tensor_field->n_accounts * tensor_field->tensor_dims;
    gdouble *result_data = g_malloc0(n_elements * sizeof(gdouble));
    
    if (g_strcmp0(operation_type, "multiply") == 0) {
        // Division algebra multiplication (simplified)
        for (gint i = 0; i < n_elements; i++) {
            result_data[i] = tensor_field->real_buffer[i] * operand_data[i];
        }
    } else if (g_strcmp0(operation_type, "add") == 0) {
        // Addition
        for (gint i = 0; i < n_elements; i++) {
            result_data[i] = tensor_field->real_buffer[i] + operand_data[i];
        }
    } else if (g_strcmp0(operation_type, "conjugate") == 0) {
        // Conjugation (negate non-real parts)
        for (gint i = 0; i < tensor_field->n_accounts; i++) {
            gdouble *account_tensor = &tensor_field->real_buffer[i * tensor_field->tensor_dims];
            gdouble *result_tensor = &result_data[i * tensor_field->tensor_dims];
            
            result_tensor[0] = account_tensor[0]; // Real part unchanged
            for (gint j = 1; j < tensor_field->tensor_dims; j++) {
                result_tensor[j] = -account_tensor[j]; // Negate imaginary parts
            }
        }
    }
    
    g_debug("Executed division algebra operation '%s' on level %d tensor field",
            operation_type, tensor_field->level);
    
    return result_data;
}

/** @} */

/** @name Utility Functions */
/** @{ */

gint gnc_agent_get_tensor_dims_for_level(gint level)
{
    if (!gnc_agent_validate_level(level)) {
        return 0;
    }
    return TENSOR_DIMS[level];
}

GncMorphismType gnc_agent_get_morphism_for_level(gint level)
{
    if (!gnc_agent_validate_level(level)) {
        return GNC_MORPHISM_PROPORTIONAL;
    }
    return LEVEL_MORPHISMS[level];
}

gboolean gnc_agent_validate_level(gint level)
{
    return (level >= 0 && level <= GNC_DIVISION_ALGEBRA_MAX_LEVEL);
}

/** @} */