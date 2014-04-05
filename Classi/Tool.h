#ifndef TOOL_H_
#define TOOL_H_

class Tool {
	public:
		Tool();
		virtual ~Tool();
		// texture;
		virtual void Usa() = 0;
};

#endif /* TOOL_H_ */
