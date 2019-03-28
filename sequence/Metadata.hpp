#pragma once
#include <Process/ProcessMetadata.hpp>

namespace sequence
{
class Model;
}

PROCESS_METADATA(
    , sequence::Model, "65d12c9c-35a6-4f42-95eb-722a640b9428",
    "sequence",                                   // Internal name
    "sequence",                                   // Pretty name
    Process::ProcessCategory::Other,              // Category
    "Other",                                      // Category
    "Description",                                // Description
    "Author",                                     // Author
    (QStringList{"Put", "Your", "Tags", "Here"}), // Tags
    {},                                           // Inputs
    {},                                           // Outputs
    Process::ProcessFlags::SupportsAll            // Flags
)
