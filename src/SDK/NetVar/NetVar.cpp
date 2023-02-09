#include "NetVar.h"

#undef GetProp

void C_NetVars::Init()
{
	const auto* client_class = I::Client->GetAllClasses();

	while (client_class != nullptr)
	{
		const auto class_info = std::make_shared<node>(0);
		RecvTable* recv_table = reinterpret_cast<RecvTable*>(client_class->m_pRecvTable);
		populate_nodes(recv_table, &class_info->nodes);
		nodes.emplace(recv_table->GetName(), class_info);

		client_class = client_class->m_pNext;
	}
}

void C_NetVars::populate_nodes(RecvTable* recv_table, map_type* map)
{
	for (auto i = 0; i < recv_table->GetNumProps(); i++)
	{
		const auto* prop = recv_table->GetPropA(i);
		const auto prop_info = std::make_shared<node>(prop->GetOffset());

		if (prop->GetType() == DPT_DataTable)
			populate_nodes(prop->GetDataTable(), &prop_info->nodes);

		map->emplace(prop->GetName(), prop_info);
	}
}

C_NetVars gNetVars;